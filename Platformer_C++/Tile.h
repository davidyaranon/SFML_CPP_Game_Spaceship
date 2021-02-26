#ifndef TILE_H
#define TILE_H

#include <vector>
#include <SFMl/Graphics.hpp>
#include <string>
#include <iostream>

class Tile {
private:
	bool setSprite(std::string fileName);
	sf::Texture texture;
	sf::Vector2f pos;
	std::string name;
	float velocity;
	float acceleration;

public:
	Tile() {}
	~Tile() {}
	Tile(std::string filePath, float posX, float posY);
	sf::Sprite getSprite();
	sf::Sprite sprite;
	std::string getTileName();
	bool hasCollided;
};

class Player : public Tile {
public:
	Player() : Tile() {}
	Player(std::string filePath, float posX, float posY);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};

class Laser : public Tile {
public:
	bool passedScreen;
	Laser() : Tile() { std::cout << "DEFAULT LASER CREATED, need one with params!" << '\n'; this->passedScreen = false; }
	Laser(std::string filePath, float posX, float posY);
	void shoot();
};

#endif
