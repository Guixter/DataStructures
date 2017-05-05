#pragma once
#include "Pile.h"

typedef struct Card {
public:
	Card(int val, int col, int bon) {
		value = val;
		color = col;
		bonus = bon;
	}

	Card() {
		value = 0;
		color = 0;
	}

	bool operator==(Card a) const {
		if (a.value == value && a.color == color)
			return true;
		else
			return false;
	}

	bool operator>(Card a) const {
		if (value > a.value)
			return true;
		else if (a.value > value)
			return false;
		else if (color > a.color)
			return true;
		else if (a.color > color)
			return false;
		else
			return false;
	}

	int bonus;
	int value;
	int color;
} Card;

class Player
{
public:
	Player();

	void addCard(const Card card);
	void winCard(const Card card);
	bool isDeckNotkEmpty();
	float countPoints();
	Card Play();

	~Player();
private:
	Pile<Card>* deck;
	Pile<Card>* winDeck;
};

