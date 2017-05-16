#pragma once
#include <string>
#include "Arbre.h"
#include <iostream>

// An eye color
enum EyeColor { BLEU, VERT, MARRON };

/*
* Une personne.
*/
struct Personne {
public:
	std::string prenom;
	std::string nom;
	int annee_naissance;
	EyeColor couleur_yeux;

	friend bool operator==(const Personne& l, const Personne& r)
	{
		return (l.prenom == r.prenom && l.nom == r.nom);
	}

	friend std::ostream& operator << (std::ostream& f, Personne p) {
		f << p.prenom << " " << p.nom;
		return f;
	}
};


class ArbreGenealogique
{
public:
	ArbreGenealogique();
	~ArbreGenealogique();

	void launch();

private:

	void menu();

	void AjouterMembre();
	void AfficherTailleHauteur();
	void ListerDescendance();
	void ListerCouleur();
	void ListerCouleurAPartirDUnePersonne();
	void CalculerMoyenneAge();


	Personne DemanderPersonne();
	Personne ChercherPersonne();


	Arbre<Personne> *arbre;
};

