#include <iostream>
#include<fstream>
#include <string>
#include "Dictionary.h"
using namespace std;

Dictionary::Dictionary(std::string filename)
{
	//arbre = new Arbre<char>();
	ifstream myReadFile;
	myReadFile.open(filename);
	char output[100];
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> output;
			ajouterMot(output);
			cout << output << endl;
		}
	}
	myReadFile.close();
}

void Dictionary::ajouterMot(std::string s) {
	Noeud<char>* a;
	cout << s.size() << endl;
}

void Dictionary::enleverMot(std::string s) {
	int tailleMot = s.size;

	if (!chercheMot(s))
		return;

	enleverMotRec(s, *racine);

	return;
}

//precondition : le mot est dans l arbre
bool Dictionary::enleverMotRec(std::string s, Noeud<char>& arbre){

	//comme le mot est present, on y est
	if (s.size == 1 && s[0] == arbre.data) {
		arbre.endWord = false;
		return true;
	}

	int tailleMot = s.size;
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

}

bool Dictionary::chercheMot(std::string s) {
	
	return chercherMotDansArbre(s,*racine);
}

bool Dictionary::chercherMotDansArbre(std::string s, Noeud<char>& arbre) {
	int tailleMot = s.size;

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
