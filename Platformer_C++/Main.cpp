#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {

	Game game = Game(1280, 720); //(window width, window height)
	game.start();

	return EXIT_SUCCESS;
}