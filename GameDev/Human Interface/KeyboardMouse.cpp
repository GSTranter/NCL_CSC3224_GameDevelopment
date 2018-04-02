/************************************************************
Class: Keyboard
File Type: cpp
Author: George Tranter
Description: Class to allow keyboard and mouse controls
************************************************************/

#include "KeyboardMouse.h"

//^~^FUNCTIONS^~^//

	//Maps inputs to events
void KeyboardMouse::bindInput(StateType currentState) {
	switch(currentState){

		case InGame:
			keyBinding[sf::Keyboard::A] = GoLeft;
			keyBinding[sf::Keyboard::D] = GoRight;
			keyBinding[sf::Keyboard::Space] = Jump;
			keyBinding[sf::Keyboard::LShift] = Dodge;
			keyBinding[sf::Keyboard::Q] = Spawn;
			break;

		case GamePause:
			keyBinding[sf::Keyboard::Escape] = MenuReturn;
			break;

		case GameOver:
			keyBinding[sf::Keyboard::Escape] = MenuReturn;
			keyBinding[sf::Keyboard::E] = Despawn;
			break;

		case Menu:
			keyBinding[sf::Keyboard::Escape] = Exit;
			keyBinding[sf::Keyboard::Q] = GameStart;

		case Victory:
			keyBinding[sf::Keyboard::Escape] = Exit;

	}
}

	//Converts input to game events, passes to event manager
void KeyboardMouse::handleInput(EventManager* eventMan, StateType currentState) {
	switch (currentState) {

		case InGame:
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				eventMan->addEvent(keyBinding[Keyboard::A]);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				eventMan->addEvent(keyBinding[Keyboard::D]);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				eventMan->addEvent(keyBinding[Keyboard::Space]);
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				eventMan->addEvent(keyBinding[Keyboard::Q]);
			}
			break;

		case GamePause:
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				eventMan->addEvent(keyBinding[Keyboard::Escape]);
			}
			break;

		case GameOver:
			if (Keyboard::isKeyPressed(Keyboard::E)) {
				eventMan->addEvent(keyBinding[Keyboard::E]);
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				eventMan->addEvent(keyBinding[Keyboard::Escape]);
			}
			break;

		case Menu:
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				eventMan->addEvent(keyBinding[Keyboard::Escape]);
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				eventMan->addEvent(keyBinding[Keyboard::Q]);
			}

		case Victory:
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				eventMan->addEvent(keyBinding[Keyboard::Escape]);
			}
	}
}

//Handle other events outside of real-time keyboard
void KeyboardMouse::handleEvents(EventManager* eventMan, RenderWindow* gameWindow, StateType currentState) {
	Event e;
	
	switch (currentState) {
	case InGame:
		while (gameWindow->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:			gameWindow->close();											break;
			case sf::Event::LostFocus:		eventMan->addEvent(Pause);										break;
			case sf::Event::KeyPressed:		if (e.key.code == sf::Keyboard::P) eventMan->addEvent(Pause);	break;
			default:																						break;
			}
		}
		break;
	case GamePause:
			while (gameWindow->pollEvent(e)) {
				switch (e.type) {
				case sf::Event::Closed:			gameWindow->close();											break;
				case sf::Event::GainedFocus:	eventMan->addEvent(Pause);										break;
				case sf::Event::KeyPressed:		if (e.key.code == sf::Keyboard::P) eventMan->addEvent(Pause);	break;
				default:																						break;
				}
			}
			break;
	case Menu:
		while (gameWindow->pollEvent(e)) {
		
		}
		break;
	}
}

	//Executes game events
void KeyboardMouse::execute(EntityManager* entities, RenderWindow* gameWindow, EventManager* eventMan) {
	eventMan->executeEvents(entities, gameWindow);
}
