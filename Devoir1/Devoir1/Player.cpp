#include "Player.h"


Player::Player()
{
	deck = new Pile<Card>(50);
	winDeck = new Pile<Card>(100);
}

void Player::addCard(const Card card) {
	deck->empiler(card);
}

void Player::winCard(const Card card) {
	winDeck->empiler(card);
}

Card Player::Play() {
	return deck->depiler();
}

bool Player::isDeckNotkEmpty() {
	return !deck->estVide();
}


float Player::countPoints() {
	float points = 0.f;
	Card current;
	while (!winDeck->estVide()) {
		 current = winDeck->depiler();
		 points += (float)current.value * (float)current.bonus * (current.color == 1 ? 1.5f : 1.f);
	}
	return points;
}

Player::~Player()
{
}
