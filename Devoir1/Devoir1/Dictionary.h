#pragma once

class Dictionary
{
private:
	template<typename E>
	class Noeud {
	public:
		E data;
		bool endWord;
		Noeud *nextLetter;
		Noeud *alternative;
		Noeud(const E& d) : nextLetter(0), data(d), alternative(0), endWord(false) { }
	};
	Noeud<char>* racine;


	//Needed Functions
	void createEndWord(std::string s, Noeud<char>* n, int index);

public:
	Dictionary(std::string filename = "");

	void ajouterMot(std::string s);
	void enleverMot(std::string s);
	bool enleverMotRec(std::string, Noeud<char>&);
	void afficherDict();
	bool chercheMot(std::string s);
	bool chercherMotDansArbre(std::string s, Noeud<char>& arbre);

	void afficherCharDict(std::string s, Noeud<char>* current);

	~Dictionary();

};

