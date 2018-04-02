/************************************************************
Class: KeyboardMouse
File Type: h
Author: George Tranter
Description: Class to allow keyboard and mouse controls
************************************************************/

#pragma once

#include "Controller.h"

using namespace std;

class KeyboardMouse : public Controller {
	private:
		map<sf::Keyboard::Key, EventNames> keyBinding;
		map<sf::Mouse::Button, EventNames> mouseBinding;
	public:
		void bindInput(StateType);
		void handleInput(EventManager*, StateType);
		void handleEvents(EventManager*, RenderWindow*, StateType);
		void execute(EntityManager*, RenderWindow*, EventManager*);
};

