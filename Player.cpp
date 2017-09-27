#include <iostream>
#include <vector>
#include "Player.h"


using namespace std;

int numberOfDice;

Player::Player() {
	m_DiceCup = DiceCup();
	m_Hand = Hand();
}

void Player::reinforce() {}
void Player::attack() {}
void Player::fortify() {}

std::vector<int> Player::RollDice(int numToRoll){
	m_DiceCup.setNumberOfDice(numToRoll);
	return m_DiceCup.rollDice();
}