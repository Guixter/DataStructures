#pragma once
#include <iostream>
#include "Arbre.h"

class Dictionary
{
public:
	Dictionary(std::string filename = "");

	void ajouterMot(std::string s);
	void enleverMot(std::string s);
	void afficherDict();
	bool chercheMot(std::string s);

	//void afficherCharDict();

	~Dictionary();

private:
	//Arbre<char>* arbre;
};

