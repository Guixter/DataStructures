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

}

void Dictionary::afficherDict() {

}

bool Dictionary::chercheMot(std::string s) {
	return true;
}


Dictionary::~Dictionary()
{
	//delete(arbre);
}
