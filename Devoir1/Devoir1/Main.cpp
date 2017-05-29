<<<<<<< HEAD
#include <iostream>
#include <sstream>
#include <time.h>
#include "Player.h"
#include "Dictionary.h"
#include "Fabrique.h"
#include "File.h"


using namespace std;

void CardGameStart(int cardsNbr) { //Distribution des cartes

	Pile<struct Card>* deck = new Pile<struct Card>(100);
	srand((unsigned int)time(NULL));

	for (int i = 0; i < cardsNbr * 2; i++) {
		deck->empiler(Card(rand() % 10 + 1, rand() % 2, rand() % 4 + 1));
	}

	Player* p1 = new Player();
	Player* p2 = new Player();

	for (int i = 0; i < cardsNbr; i++) {
		p1->addCard(deck->depiler());
		p2->addCard(deck->depiler());
	}

	while (p1->isDeckNotkEmpty() && p2->isDeckNotkEmpty()) {

		Card CardP1 = p1->Play();
		Card CardP2 = p2->Play();
		cout << " P1 : " << CardP1.value << " - " << CardP1.color << " | P2 :" << CardP2.value << " - " << CardP2.color;

		if (CardP1 == CardP2) {
			p1->winCard(CardP1);
			p2->winCard(CardP2);
			cout << " (EGALITE)" << endl;
		} else if (CardP1 > CardP2) {
			p1->winCard(CardP1);
			p1->winCard(CardP2);
			cout << " (P1)" << endl;
		} else if (CardP2 > CardP1) {
			p2->winCard(CardP2);
			p2->winCard(CardP1);
			cout << " (P2)" << endl;
		} else
			cout << "ERROR" << endl;
	}

	float PointsP1 = p1->countPoints();
	float PointsP2 = p2->countPoints();
	cout << PointsP1 << " - " << PointsP2 << " : ";

	if (PointsP1 == PointsP2) {
		cout << "No Winner" << endl;
	} else if (PointsP1 > PointsP2) {
		cout << "P1 is the winner" << endl;
	} else if (PointsP2 > PointsP1) {
		cout << "P2 is the winner" << endl;
	}
	cin.clear();

	cout << "Do you want to replay ? (O/N)" << endl;

	char Choice[100];
	cin >> Choice;

	if (Choice[0] == 'O') {
		CardGameStart(cardsNbr);
	} else {
		return;
	}
}

void CardGame() {

	int cardsNumber;

	cout << "How many cards do you want ?" << endl;

	cin >> cardsNumber;

	cin.clear();

	cin.ignore(1000, '\n');

	//Start Card Game

	if (cardsNumber > 50)

		cardsNumber = 50;

	else if (2 > cardsNumber)

		cardsNumber = 2;

	CardGameStart(cardsNumber);

}



void Factory() {

	Fabrique *f = new Fabrique();

	f->launch();

	delete f;

}



void DictionnaryF() {
	Dictionary* dictionary = new Dictionary("FichierTest/g.dico");

	int choice = -1;
	while (choice != 0) {
		cout << "------------------------" << endl;
		cout << "Que voulez vous faire avec le dictionnaire ?" << endl << endl;
		cout << "1 - Afficher le dictionnaire :" << endl;
		cout << "2 - Ajouter un dictionnaire" << endl;
		cout << "3 - Chercher un mot" << endl;
		cout << "4 - Supprimer un mot dictionnaire" << endl;
		cout << "5 - Ajouter un mot au dictionnaire" << endl;
		cout << "0 - Quitter le dictionnaire" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
		cin.clear();

		char word[100];

		switch (choice) {
		case 0:
			break;
		case 1:
			dictionary->afficherDict();
			break;
		case 2:
			cout << "Donner le nom du fichier : " << endl;
			cin >> word;
			dictionary->ajouterDico("FichierTest/"+ (string)word +".dico");
			break;
		case 3:
			cin.clear();
			cout << "Mot recherch� : " << endl;
			cin >> word;
			cout << dictionary->chercheMot(word) << endl;
			break;
		case 4:
			cout << "Mot � supprimer : " << endl;
			cin >> word;
			dictionary->enleverMot(word);
			break;
		case 5:
			cout << "Mot � ajouter : " << endl;
			cin >> word;
			dictionary->ajouterMot(word);
			break;
		default:
			break;
		}
	}

}



void FamilyTree() {

}



void DoubleLinkedList() {

}



void menu() {

	int choice = -1;

	while (choice != 0) {

		cout << "------------------------" << endl;

		cout <<  "Choix de l'exercice :" << endl << endl;

		cout << "1 - Cardgame :" << endl;

		cout << "2 - Factory" << endl;

		cout << "3 - Dictionary" << endl;

		cout << "4 - TODO" << endl;

		cout << "5 - TODO" << endl;

		cout << "0 - EXIT" << endl;



		cin >> choice;

		cin.clear();

		cin.ignore(1000, '\n');

		cout << endl;



		switch (choice) {

		case 0:

			break;

		case 1:

			CardGame();

			break;

		case 2:

			Factory();

			break;

		case 3:

			DictionnaryF();

			break;

		case 4:

			FamilyTree();

			break;

		case 5:

			DoubleLinkedList();

			break;

		default:

			break;

		}

	}

}





int main() {
	menu();

	system("PAUSE");

	return 0;
}

=======
#include <iostream>
#include <sstream>
#include <time.h>
#include "Player.h"
#include "Fabrique.h"
#include "File.h"
#include "FamilyTree.h"

using namespace std;

void CardGameStart(int cardsNbr) { //Distribution des cartes
	Pile<struct Card>* deck = new Pile<struct Card>(100);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < cardsNbr * 2; i++) {
		deck->empiler(Card(rand() % 10 + 1, rand() % 2, rand() % 4 + 1));
	}
	Player* p1 = new Player();
	Player* p2 = new Player();

	for (int i = 0; i < cardsNbr; i++) {
		p1->addCard(deck->depiler());
		p2->addCard(deck->depiler());
	}

	while (p1->isDeckNotkEmpty() && p2->isDeckNotkEmpty()) {
		Card CardP1 = p1->Play();
		Card CardP2 = p2->Play();
		cout << " P1 : " << CardP1.value << " - " << CardP1.color << " | P2 :" << CardP2.value << " - " << CardP2.color;
		if (CardP1 == CardP2) {
			p1->winCard(CardP1);
			p2->winCard(CardP2);
			cout << " (EGALITE)" << endl;
		}
		else if (CardP1 > CardP2) {
			p1->winCard(CardP1);
			p1->winCard(CardP2);
			cout << " (P1)" << endl;
		}
		else if (CardP2 > CardP1) {
			p2->winCard(CardP2);
			p2->winCard(CardP1);
			cout << " (P2)" << endl;
		}
		else
			cout << "ERROR" << endl;

	}
	float PointsP1 = p1->countPoints();
	float PointsP2 = p2->countPoints();
	cout << PointsP1 << " - " << PointsP2 << " : ";
	if (PointsP1 == PointsP2) {
		cout << "No Winner" << endl;
	}
	else if (PointsP1 > PointsP2) {
		cout << "P1 is the winner" << endl;
	}
	else if (PointsP2 > PointsP1) {
		cout << "P2 is the winner" << endl;
	}
	cin.clear();

	cout << "Do you want to replay ? (O/N)" << endl;
	char Choice[100];
	cin >> Choice;
	if (Choice[0] == 'O') {
		CardGameStart(cardsNbr);
	}
	else {
		return;
	}
}


void CardGame() {
	int cardsNumber;
	cout << "How many cards do you want ?" << endl;
	cin >> cardsNumber;
	cin.clear();
	cin.ignore(1000, '\n');
	//Start Card Game
	if (cardsNumber > 50)
		cardsNumber = 50;
	else if (2 > cardsNumber)
		cardsNumber = 2;
	CardGameStart(cardsNumber);
}

void Factory() {
	Fabrique *f = new Fabrique();
	f->launch();
	delete f;
}

void Dictionnary() {
}

void launchFamilyTree() {
	FamilyTree *t = new FamilyTree();
	t->launch();
	delete t;
}

void DoubleLinkedList() {
}

void menu() {
	int choice = -1;
	while (choice != 0) {
		cout << "------------------------" << endl;
		cout <<  "Choix de l'exercice :" << endl << endl;
		cout << "1 - Cardgame :" << endl;
		cout << "2 - Factory" << endl;
		cout << "3 - TODO" << endl;
		cout << "4 - Arbre genealogique" << endl;
		cout << "5 - TODO" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			CardGame();
			break;
		case 2:
			Factory();
			break;
		case 3:
			Dictionnary();
			break;
		case 4:
			launchFamilyTree();
			break;
		case 5:
			DoubleLinkedList();
			break;
		default:
			break;
		}
	}
}


int main() {

	menu();

	//system("PAUSE");
	return 0;
}
>>>>>>> Exercice4
