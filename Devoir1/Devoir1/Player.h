#pragma once
#include "Pile.h"

typedef struct Card {
public:
	Card(int val, int col) {
		value = val;
		color = col;
	}

	Card() {
		value = 0;
		color = 0;
	}

	int value;
	int color;
} Card;

class Player
{
public:
	Player();

	void addCard(const Card card);

	~Player();
private:
	Pile<Card>* deck;
};

