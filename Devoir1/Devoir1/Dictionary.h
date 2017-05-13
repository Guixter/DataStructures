#pragma once

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
	template<typename E>
	class Noeud {
	public:
		E data;
		Noeud *nextLetter;
		Noeud *alternative;
		Noeud(const E& d) : nextLetter(0), data(d), alternative(0) { }
	};
	Noeud<char>* racine;
};

