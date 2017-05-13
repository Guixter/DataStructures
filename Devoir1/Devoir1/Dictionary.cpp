#include <iostream>
#include<fstream>
#include <string>
#include "Dictionary.h"
using namespace std;

Dictionary::Dictionary(std::string filename)
{
	racine = new Noeud<char>('/');

	//arbre = new Arbre<char>();
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
	std::string remainingS(s);
	int i(0), sSize(s.size());

	while (i < sSize) {

		while (current->data != s[i] && current->alternative != 0) {
			current = current->alternative;
		}
		if (current->data != s[i]) {
			Noeud<char>* newNoeud = new Noeud<char>(s[i]);
			current->alternative = newNoeud;
			current = current->alternative;
			createEndWord(s, current, i);
			break;
		} else if (current->data == s[i]) {
			if (current->nextLetter == 0) {
				createEndWord(s, current, i);
				break;
			}
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

}

void Dictionary::afficherDict() {
	afficherCharDict("", racine);
}

bool Dictionary::chercheMot(std::string s) {
	return true;
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
