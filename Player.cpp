#include "Player.h"
#include <string.h>

Player::Player() {
}

Player::~Player() {
}

int Player::isLose() {
    return this->lose;
}

int Player::isWin() {
    return this->win;
}

char* Player::getNome() {
    return this->nome;
}

void Player::setNome(char nome[]) {
    strcpy(this->nome, nome);
}

void Player::setLose(int lose) {
    this->lose = lose;
}

void Player::setWin(int win) {
    this->win = win;
}

float Player::getTimer() {
    return timer;
}

void Player::setTimer(float timer) {
    this->timer = timer;
}

