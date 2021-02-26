#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include "Game.h"
#include "Tile.h"

Game::Game(float windowWidth, float windowHeight)
	: gameName{ "Platformer_Test" }
    , videoMode(sf::VideoMode(1280, 720))
	, window(new sf::RenderWindow(videoMode, gameName))
	, score{ 0 }
	, screen{ 0 }
	, level{ 1 }
	, laserCount{ 10 }
	, isStarted{ false } //Initializer list allows for easy initialization in C++
{
	srand(time(NULL));
	this->window->setFramerateLimit(60);
	this->initText();
}


void Game::initText() {
	if (!this->font.loadFromFile("Texts/ARCADE.ttf")) {
		std::cout << "ERROR IN LOADING TEXT" << std::endl;
	}
	this->menuText.setFont(font);
	this->menuText.setString("PRESS ENTER TO START GAME");
	this->menuText.setCharacterSize(50);
	this->menuText.setPosition(sf::Vector2f(312.5, 325));
	this->menuText.setFillColor(sf::Color::White);
	this->menuText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->tScore.setFont(font);
	this->tScore.setString("0");
	this->tScore.setCharacterSize(24);
	this->tScore.setPosition(sf::Vector2f(0,0));
	this->tScore.setFillColor(sf::Color::White);
	this->tScore.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->tLaserCount.setFont(font);
	this->tLaserCount.setString(std::to_string(laserCount) + " LASERS REMAINING");
	this->tLaserCount.setCharacterSize(20);
	this->tLaserCount.setPosition(sf::Vector2f(1, 5));
	this->tLaserCount.setFillColor(sf::Color::White);
	this->tLaserCount.setStyle(sf::Text::Bold);
}

void Game::checkBounds() {
	//PLAYER
	if (this->player->sprite.getGlobalBounds().left <= 0.f) { //LEFT BOUND
		this->player->sprite.setPosition(0.f, this->player->sprite.getPosition().y);
	}
	else if (this->player->sprite.getGlobalBounds().left + this->player->sprite.getGlobalBounds().width  >= this->window->getSize().x) { //RIGHT BOUND
		this->player->sprite.setPosition(1280 - 60, this->player->sprite.getPosition().y);
	}
	if (this->player->sprite.getGlobalBounds().top <= 0.f) { //UPPER BOUND
		this->player->sprite.setPosition(this->player->sprite.getPosition().x, 0.f);
	}
	else if (this->player->sprite.getGlobalBounds().top >= 720 - 60) { //LOWER BOUND
		this->player->sprite.setPosition(this->player->sprite.getPosition().x, 720 - 60);
	}
	//LASERS
	uint16_t tempCount = 0;
	for (int i = 0, j = 0; i < this->lasers.size(); i++, j++) {
		if (this->lasers[i]->sprite.getGlobalBounds().left + this->lasers[i]->sprite.getGlobalBounds().width >= this->window->getSize().x) { //RIGHT BOUND
			this->lasers[i]->passedScreen = true;
		}
		if (j < this->enemies.size()) {
			if (this->lasers[i]->sprite.getGlobalBounds().intersects(this->enemies[j]->sprite.getGlobalBounds())) {
				this->lasers[i]->hasCollided = true;
				this->enemies[j]->hasCollided = true;
			}
		}
		if (this->lasers[i]->passedScreen) {
			std::cout << "Laser " << i << " passed screen" << '\n';
			tempCount++;
		}
	}
	if (tempCount == lasers.size()) {
		lasers.clear();
	}
}

void Game::drawMenuScreen() {
	this->window->draw(this->menuText);
}

void Game::drawLevel() {
	for (int i = 0; i < this->enemies.size(); i++) {
		if (!this->enemies[i]->hasCollided) {
			this->window->draw(this->enemies[i]->sprite);
		}
	}
	for (int i = 0; i < this->lasers.size(); i++) {
		if (!this->lasers[i]->hasCollided) {
			this->window->draw(this->lasers[i]->sprite);
		}
	}
	this->window->draw(this->player->getSprite());
	this->window->draw(this->tLaserCount);
}

void Game::loadLevelOne() {
	//for(int i = 0; i < )
	Player* lplayer = new Player("Sprites/Ship.png", 0, 660);
	this->player = std::unique_ptr<Player>(lplayer);
	
	std::unique_ptr<Tile> e1(new Tile("Sprites/Enemy.png", 800, 30));
	this->enemies.emplace_back(std::move(e1));
	std::unique_ptr<Tile> e2(new Tile("Sprites/Enemy.png", 700, 199));
	this->enemies.emplace_back(std::move(e2));
	this->enemies[0]->sprite.setScale(1.25, 1.25);
	this->enemies[1]->sprite.setScale(1.25, 1.25);
}

void Game::makeLaser() {
	if (laserCount > 0) {
		this->tLaserCount.setString(std::to_string(--laserCount) + " LASERS REMAINING");
		std::unique_ptr<Laser> l(new Laser("Sprites/Laser.png", this->player->sprite.getPosition().x + 60, this->player->sprite.getPosition().y + 30));
		lasers.emplace_back(std::move(l));
	}
}

void Game::start() { //GAME LOOP HERE
	while (this->window->isOpen()) {
		this->window->clear();
		while (this->window->pollEvent(this->event)) {
			switch (this->event.type) {
			case sf::Event::LostFocus :
				std::cout << "GAME PAUSED" << std::endl;
				//this->pause();
				break;
			case sf::Event::GainedFocus :
				std::cout << "GAME UNPAUSED" << std::endl;
				//this->resume();
				break;
			case sf::Event::Closed :
				std::cout << "WINDOW CLOSING" << std::endl;
				window->close();
				break;
			case sf::Event::KeyPressed :
				switch (this->event.key.code) {
				case sf::Keyboard::Enter :
					if (!this->isStarted) {
						this->isStarted = true;
						this->loadLevelOne();
					}
					break;
				case sf::Keyboard::Space: //Polling event allows delay when firing!
					if (this->isStarted) {
						this->makeLaser();
					}
					break;
				}

			}
		}
		this->window->clear();
		if (!this->isStarted) {
			this->drawMenuScreen();
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				std::cout << "LEFT PRESSED" << '\n';
				this->player->moveLeft();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				std::cout << "RIGHT PRESSED" << '\n';
				this->player->moveRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				std::cout << "UP PRESSED" << '\n';
				this->player->moveUp();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				std::cout << "DOWN PRESSED" << '\n';
				this->player->moveDown();
			}
			for (int i = 0; i < this->lasers.size(); i++) {
				this->lasers[i]->shoot();
			}
			this->checkBounds();
			this->drawLevel();
		}

		this->window->display();

	}
}

void Game::updateLevel() {
	//this->tiles.clear();
	//this->lasers.clear();
}