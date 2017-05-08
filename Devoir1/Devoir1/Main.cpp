#include <iostream>
#include <time.h>
#include "Player.h"
#include "Fabrique.h"
#include "File.h"

using namespace std;

void CardGameStart() { //Distribution des cartes
	Pile<struct Card>* deck = new Pile<struct Card>(100);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++) {
		deck->empiler(Card(rand() % 10 +1, rand() % 2, rand() % 4 +1));
	}
	Player* p1 = new Player();
	Player* p2 = new Player();

	for (int i = 0; i < 50; i++) {
		p1->addCard(deck->depiler());
		p2->addCard(deck->depiler());
	}

	while (p1->isDeckNotkEmpty() && p2->isDeckNotkEmpty()) {
		Card CardP1 = p1->Play();
		Card CardP2 = p2->Play();
		if (CardP1 == CardP2) {
			p1->winCard(CardP1);
			p2->winCard(CardP2);
		}
		else if (CardP1 > CardP2) {
			p1->winCard(CardP1);
			p1->winCard(CardP2);
		}
		else if (CardP2 > CardP1) {
			p2->winCard(CardP2);
			p2->winCard(CardP1);
		}
		else
			cout << "ERROR" << endl;

//		cout << CardP1.value << " - " << CardP1.color << " | " << CardP2.value << " - " << CardP2.color << "EGALITE" << endl;

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
	else if (PointsP2 > PointsP1){
		cout << "P2 is the winner" << endl;
	}

}


void CardGame() {
	CardGameStart();
}

void Factory() {
	Fabrique *f = new Fabrique();
	f->launch();
	delete f;
}

void Dictionnary() {
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
		cout << "3 - TODO" << endl;
		cout << "4 - TODO" << endl;
		cout << "5 - TODO" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
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

	//system("PAUSE");
	return 0;
}
