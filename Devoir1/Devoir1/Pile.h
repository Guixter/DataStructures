#pragma once
#include <iostream>
using namespace std;

template <typename T> 
class Pile {
public:
	// constructeurs et destructeurs  
	Pile(int max = 100); //constructeur  
	Pile(const Pile&); //constructeur copie 
	~Pile(); //destructeur      
	// Modificateurs  
	void empiler(const T&);  
	T depiler();  //Sélecteurs 
	bool estVide()const;  
	int getTaille() const { return taille };
	const T& getSommet() const { return sommet }; // consulte l’élément au sommet  
	//surcharge d'opérateurs  
	const Pile<T>& operator=(const Pile<T>&);
//	friend ostream& operator<<(ostream& , const Pile<T>& );

private:
	int tailleMax;
	int taille;
	T* tab;
	int sommet;
};

template <typename T>
Pile<T>::Pile(int max) /*throw (std::bad_alloc) */ {
	tab = new T[max];
	sommet = -1;  //valeur dummypour indiquer que la pile est vide. 
	tailleMax = max;
	taille = 0;
}

template <typename T>
Pile<T>::Pile(const Pile<T>& p) {
	tab = new T[p.tailleMax];
	tailleMax = p.tailleMax;

	for (inti = 0; i< tailleMax; i += 1)
		tab[i] = p.tab[i];

	sommet = p.sommet;
}

template <typename T>
T Pile<T>::depiler() /*throw(std::logic_error)*/ {
	if (!estVide())
		return tab[sommet--];
	else
		throw logic_error("Depiler: la pile est vide!");
}

template <typename T>
bool Pile<T>::estVide() const {
	return(sommet == -1);
}

template <typename T>
void Pile<T> ::empiler(const T& e) /*throw (std::length_error) */ {
	if (sommet + 1 < tailleMax) {
		sommet += 1; // a += b a = a+ b 
		tab[sommet] = e;
	}
	else
		throw length_error("Empiler:la pile est pleine\n");
}
/*
template <typename T>
void Pile<T>::resize() /*throw (bad_alloc)*/ /*{
int nouvelleTaille = sommet++ * 2;
tab = new T[nouvelleTaille];

for (inti = 0; i< sommet; i++)
tab[i] = p.tab[i];

tailleMax = nouvelleTaille;
}*/

template <typename T>
const Pile<T>& Pile<T>::operator=(const Pile<T>& p) /*throw (bad_alloc) */ {

	if (tab != 0)
		delete[] tab;  //on nettoie l’objet qu’on veux écraser 

	tab = new T[p.tailleMax];
	tailleMax = p.tailleMax;

	for (inti = 0; i< tailleMax; i += 1)
		tab[i] = p.tab[i];

	sommet = p.sommet;
	return(*this); //retourner : une référence sur l’objet courant 
}

template <typename T>
Pile<T>::~Pile()
{
}
/*
template <typename T>
ostream & operator<<(ostream & os, const Pile<T>& p)
{
for (int i = 0; i < p.sommet; i++)
os << p.tab[i];
return os;
}
*/