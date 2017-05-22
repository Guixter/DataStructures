#include "ArbreGenealogique.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

ArbreGenealogique::ArbreGenealogique() {}

ArbreGenealogique::~ArbreGenealogique()
{
	delete arbre;
}

void ArbreGenealogique::launch() {
	// Créer l'arbre et demander la racine
	cout << "Choisir la racine de l'arbre (le plus vieux) : " << endl;
	Personne p = DemanderPersonne();
	arbre = new Arbre<Personne>(p);

	// Appeler le menu
	menu();
}

Personne ArbreGenealogique::DemanderPersonne() {
	Personne p;
	p.prenom = "";
	p.nom = "";
	p.annee_naissance = 0;

	// Prénom
	while (p.prenom.compare("") == 0) {
		cout << "------------------------" << endl;
		cout << "Prenom ? ";

		getline(cin, p.prenom);
		cin.clear();
		cout << endl;
	}


	// Nom
	while (p.nom.compare("") == 0) {
		cout << "------------------------" << endl;
		cout << "Nom ? ";

		getline(cin, p.nom);
		cin.clear();
		cout << endl;
	}

	// Année de naissance
	while (p.annee_naissance <= 0) {
		cout << "------------------------" << endl;
		cout << "Annee de naissance ? ";

		cin >> p.annee_naissance;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
	}

	// Couleur d'yeux
	int choix = -1;
	while (choix < 0 || choix > 2) {
		cout << "------------------------" << endl;
		cout << "Couleur d'yeux ? (Bleu = 0, Vert = 1, Marron = 2) ";

		cin >> choix;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
	}
	p.couleur_yeux = static_cast<EyeColor>(choix);

	return p;
}

Personne ArbreGenealogique::ChercherPersonne() {
	string prenom, nom;
	Personne p;
	bool cont = true;

	while (cont) {
		prenom = "";
		nom = "";

		// Prénom
		while (prenom.compare("") == 0) {
			cout << "------------------------" << endl;
			cout << "Prenom ? ";

			getline(cin, prenom);
			cin.clear();
			cout << endl;
		}

		// Nom
		while (nom.compare("") == 0) {
			cout << "------------------------" << endl;
			cout << "Nom ? ";

			getline(cin, nom);
			cin.clear();
			cout << endl;
		}

		auto _aux = [prenom, nom, &p, &cont](Personne elt) {
			if (elt.prenom.compare(prenom) == 0 && elt.nom.compare(nom) == 0) {
				p = elt;
				cont = false;
			}
		};

		arbre->appliquerSuffixe(_aux);
	}

	return p;
}

void ArbreGenealogique::menu() {
	int choice = -1;
	while (choice != 0) {
		cout << "------------------------" << endl;
		cout << "Que voulez-vous ?" << endl << endl;
		cout << "1 - Ajouter un membre :" << endl;
		cout << "2 - Taille et hauteur de l'arbre" << endl;
		cout << "3 - Lister la descendance d'une personne" << endl;
		cout << "4 - Lister par couleur d'yeux" << endl;
		cout << "5 - Lister les descendants d'une personne ayant la meme couleur d'yeux" << endl;
		cout << "6 - Moyenne d'age" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			AjouterMembre();
			break;
		case 2:
			AfficherTailleHauteur();
			break;
		case 3:
			ListerDescendance();
			break;
		case 4:
			ListerCouleur();
			break;
		case 5:
			ListerCouleurAPartirDUnePersonne();
			break;
		case 6:
			CalculerMoyenneAge();
			break;
		default:
			break;
		}
	}
}

void ArbreGenealogique::AjouterMembre() {
	// Trouver la personne parente
	cout << "Choisissez la personne parente" << endl;
	Personne parent = ChercherPersonne();

	bool cont = true;
	Personne p;
	while (cont) {
		// Créer la personne à ajouter
		cout << "Entrez les donnees de l'enfant (15 ans de difference avec son parent minimum)" << endl;
		p = DemanderPersonne();

		if (p.annee_naissance <= parent.annee_naissance + 15) {
			cout << "L'enfant doit avoir au moins 15 ans de difference avec son parent." << endl;
		} else {
			cont = false;
		}
	}

	// Ajouter la personne à l'arbre
	arbre->ajouter(parent, p);
}

void ArbreGenealogique::AfficherTailleHauteur() {
	cout << "La taille de l'arbre est : " << arbre->taille() << endl;
	cout << "La hauteur de l'arbre est : " << arbre->hauteur() << endl;
	system("pause");
}

void ArbreGenealogique::ListerDescendance() {
	// Chercher la personne
	cout << "Choisissez la personne" << endl;
	Personne p = ChercherPersonne();

	// Type de parcours
	int choix = -1;
	while (choix < 0 || choix > 2) {
		cout << "Parcours ? (Prefixe = 0, Infixe = 1, Suffixe = 2) ";

		cin >> choix;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
	}

	auto _aux = [](Personne elt) {
		cout << "* " << elt.prenom << " " << elt.nom << endl;
	};

	if (choix == 0) {
		arbre->appliquerPrefixe(_aux, p);
	}
	else if (choix == 1) {
		arbre->appliquerInfixe(_aux, p);
	}
	else if (choix == 2) {
		arbre->appliquerSuffixe(_aux, p);
	}
	system("pause");
}

void ArbreGenealogique::ListerCouleur() {
	// Couleur d'yeux
	int choix = -1;
	while (choix < 0 || choix > 2) {
		cout << "Couleur d'yeux ? (Bleu = 0, Vert = 1, Marron = 2) ";

		cin >> choix;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
	}
	EyeColor c = static_cast<EyeColor>(choix);

	auto _aux = [c](Personne elt) {
		if (elt.couleur_yeux == c) {
			cout << "* " << elt.prenom << " " << elt.nom << endl;
		}
	};
	arbre->appliquerPrefixe(_aux);
	system("pause");
}

void ArbreGenealogique::ListerCouleurAPartirDUnePersonne() {
	// Chercher la personne
	cout << "Choisissez la personne" << endl;
	Personne p = ChercherPersonne();

	auto _aux = [p](Personne elt) {
		if (elt.couleur_yeux == p.couleur_yeux) {
			cout << "* " << elt.prenom << " " << elt.nom << endl;
		}
	};
	arbre->appliquerPrefixe(_aux, p);
	system("pause");
}

void ArbreGenealogique::CalculerMoyenneAge() {
	int sommeAnnee = 0;

	auto _aux = [&sommeAnnee](Personne elt) {
		sommeAnnee += elt.annee_naissance;
	};

	arbre->appliquerPrefixe(_aux);
	sommeAnnee /= arbre->taille();

	cout << "Age moyen : " << (2017 - sommeAnnee) << endl;
	system("pause");
}