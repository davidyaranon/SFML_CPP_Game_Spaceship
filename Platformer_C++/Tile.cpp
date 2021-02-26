#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

Tile::Tile(std::string filePath, float posX, float posY)
	: velocity{ 5.0 }
	, acceleration { 2.0 }
	, hasCollided{false}
{
	this->name = filePath;
	if (!this->setSprite(filePath)) {
		std::cout << "COULD NOT LOAD SPRITE FROM PATH " << filePath << '\n';
		return;
	}
	this->pos = sf::Vector2f(posX, posY);
	this->sprite.setPosition(pos);
	//this->sprite.setScale(0.5, 0.5);
	//sf::Color color(14,24,53,0);
	//this->sprite.setColor(color);
}

bool Tile::setSprite(std::string filePath) {
	if (!this->texture.loadFromFile(filePath)) {
		return false;
	}
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));

	return true;
}

sf::Sprite Tile::getSprite() {
	return this->sprite;
}

std::string Tile::getTileName() {
	return this->name;
}



Player::Player(std::string filePath, float posX, float posY) : Tile(filePath, posX, posY) {
	std::cout << "Generating Player" << '\n';
}


void Player::moveLeft() {
	this->sprite.move(-7.5, 0);
}

void Player::moveRight() {
	this->sprite.move(7.5, 0);
}

void Player::moveUp() {
	this->sprite.move(0, -5);
}

void Player::moveDown() {
	this->sprite.move(0, 5);
}

Laser::Laser(std::string filePath, float posX, float posY)
	: Tile(filePath, posX, posY)
	, passedScreen{ false }
{
	std::cout << "LASER GENERATED" << '\n';
	this->sprite.setTextureRect(sf::IntRect(0, 0, 40, 5));
}

void Laser::shoot() {
	this->sprite.move(10, 0);
}

