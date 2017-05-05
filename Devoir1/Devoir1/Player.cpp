#include "Player.h"


Player::Player()
{
	deck = new Pile<Card>(50);
}

void Player::addCard(const Card card) {
	deck->empiler(card);
}


Player::~Player()
{
}
