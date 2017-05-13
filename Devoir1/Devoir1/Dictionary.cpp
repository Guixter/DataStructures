#include <iostream>
#include<fstream>
#include <string>
#include "Dictionary.h"
using namespace std;

Dictionary::Dictionary(std::string filename)
{
	racine = new Noeud<char>('/');

	//arbre = new Arbre<char>();
	ajouterDico(filename);
}

void Dictionary::ajouterDico(std::string filename) {
	ifstream myReadFile;
	myReadFile.open(filename);
	char output[100];
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> output;
			ajouterMot(output);
		}
	}
	myReadFile.close();
}


void Dictionary::ajouterMot(std::string s) {
	Noeud<char>* current(racine);
	Noeud<char>* parent(racine);
	std::string remainingS(s);
	int i(0), sSize(s.size());

	while (i < sSize) {

		while (current->data != s[i] && current->alternative != 0 && (int)current->alternative->data <= (int)s[i]) {
			current = current->alternative;
		}
		if (current->data != s[i]) {
			Noeud<char>* newNoeud = new Noeud<char>(s[i]);
			if ((int)current->data > (int)s[i] && current->alternative == 0 && parent != racine) {
				parent->nextLetter = newNoeud;
				newNoeud->alternative = current;
				current = newNoeud;
			}
			else {
				newNoeud->alternative = current->alternative;
				current->alternative = newNoeud;
				current = current->alternative;

			}

			createEndWord(s, current, i);
			break;
		} else if (current->data == s[i]) {
			if (current->nextLetter == 0) {
				createEndWord(s, current, i);
				break;
			}
			parent = current;
			current = current->nextLetter;
		} else {
			cout << "Unknown error" << endl;
		}
		i++;
	}
}

void Dictionary::createEndWord(std::string s, Noeud<char>* n, int index) {
	int i(index);
	Noeud<char>* current = n;
	i++;
	while (i < s.size()) {
		Noeud<char>* newNoeud = new Noeud<char>(s[i]);
		current->nextLetter = newNoeud;
		current = current->nextLetter;
		i++;
	}
	current->endWord = true;
}


void Dictionary::enleverMot(std::string s) {
	int tailleMot = s.size();

	if (!chercheMot(s))
		return;

	enleverMotRec(s, *racine);

	return;
}

//precondition : le mot est dans l arbre
bool Dictionary::enleverMotRec(std::string s, Noeud<char>& arbre){

	//comme le mot est present, on y est
	if (s.size() == 1 && s[0] == arbre.data) {
		arbre.endWord = false;
		return true;
	}

	int tailleMot = s.size();
	std::string sousChaine = s.substr(1, tailleMot);

	//si la lettre suivante appartient au mot
	if (enleverMotRec(sousChaine, *arbre.nextLetter)) {
		//si la lettre n est plus utilisee, la retirer
		if (arbre.nextLetter->nextLetter == 0 && !arbre.nextLetter->endWord) {

			//delete *(arbre.nextLetter);
			arbre.nextLetter = arbre.nextLetter->alternative;
		}
		//on doit etre modifie par le predecesseur, car on appartient au mot
		return true;
	}
	//si la lettre alternative appartient au mot
	if (enleverMotRec(s, *arbre.alternative)) {
		if (arbre.alternative->nextLetter == 0 && !arbre.alternative->endWord) {

			//delete *(arbre.alternative);
			arbre.alternative = arbre.alternative->alternative;
		}
		//on n appartient pas au mot, on ne doit pas etre modifie
		return false;
	}
	//qu on appartienne au mot ou non, nos fils n ont pas ete modifies donc on ne doit pas etre modifie
	return false;
}

void Dictionary::afficherDict() {
	afficherCharDict("", racine);
}

bool Dictionary::chercheMot(std::string s) {
	
	return chercherMotDansArbre(s,*racine);
}

bool Dictionary::chercherMotDansArbre(std::string s, Noeud<char>& arbre) {
	int tailleMot = s.size();

	if (tailleMot == 0)
		return false;

	if (tailleMot == 1 && s[0] == arbre.data && arbre.endWord) {//&& arbre.finDeMot)
		return true;
	}

	if (arbre.alternative == 0 && (s[0] != arbre.data)) {
		return false;
	}

	std::string sousChaine = s.substr(1, tailleMot);
	if (s[0] == arbre.data) {		
		return chercherMotDansArbre(sousChaine, *(arbre.nextLetter));	
	}
	else
	{
		return chercherMotDansArbre(s, *(arbre.alternative));
	}
}


Dictionary::~Dictionary()
{
	//delete(arbre);
}

void Dictionary::afficherCharDict(std::string s, Noeud<char>* current) {
	if (current->endWord) {
		cout << s + current->data << endl;
	}

	if (current->nextLetter !=0) {
		afficherCharDict(s + current->data, current->nextLetter);
	}
	if (current->alternative != 0) {
		afficherCharDict(s, current->alternative);
	}
}
