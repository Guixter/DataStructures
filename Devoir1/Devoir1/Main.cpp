#include <iostream>
#include <time.h>
#include "Player.h"
using namespace std;

void CardGameStart() {
	Pile<struct Card>* deck = new Pile<struct Card>(100);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++) {
		deck->empiler(Card(rand() % 10, rand() % 4));
	}
	Player* p1 = new Player();
	Player* p2 = new Player();

	for (int i = 0; i < 50; i++) {
		p1->addCard(deck->depiler());
		p2->addCard(deck->depiler());
	}


}

int main() {
	CardGameStart();
	system("PAUSE");
	return 0;
}