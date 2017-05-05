#include <iostream>
#include <sstream>
#include <time.h>
#include "Player.h"
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


int main() {
	int cardsNumber;
	cout << "How many cards do you want ?" << endl;
	cin >> cardsNumber;
	//Start Card Game
	if (cardsNumber > 50)
		cardsNumber = 50;
	else if (2 > cardsNumber)
		cardsNumber = 2;
	CardGameStart(cardsNumber);
	
	system("PAUSE");
	return 0;
}