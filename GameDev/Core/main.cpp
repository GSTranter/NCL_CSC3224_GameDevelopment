#include "Core.h"
#include "Physics.h"

using namespace sf;

int main() {

	RenderWindow* gameWindow = new RenderWindow(sf::VideoMode(1280, 720), "Game Dev", sf::Style::Default);
	gameWindow->setFramerateLimit(60);
	Core game;

	game.ini(gameWindow);
	while (gameWindow->isOpen()) {
		game.update();
	}
	game.shutdown();

	return 0;
}