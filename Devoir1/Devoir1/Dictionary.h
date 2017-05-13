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
	void afficherDict();
	bool chercheMot(std::string s);

	void afficherCharDict(std::string s, Noeud<char>* current);

	~Dictionary();

};

