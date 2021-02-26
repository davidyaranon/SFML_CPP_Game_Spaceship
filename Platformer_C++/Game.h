#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"

class Game {
private:
	std::unique_ptr<Player> player;
	sf::VideoMode videoMode;
	std::unique_ptr<sf::RenderWindow> window;
	std::vector<std::unique_ptr<Laser>> lasers;
	std::vector<std::unique_ptr<Tile>> enemies; //Enemy tiles
	sf::Text menuText, tScore, tLaserCount;
	sf::Font font;
	sf::Event event;
	std::string gameName;
	uint16_t score, screen, level, laserCount;
	bool isStarted;

	void initText();
	void loadLevelOne();
	void drawLevel();
	void drawMenuScreen();
	void updateLevel();
	void checkBounds();
	void makeLaser();

public:
	Game(float, float);
	void start();

};


#endif

