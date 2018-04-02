/************************************************************
Class: InputManager
File Type: cpp
Author: George Tranter
Description: Class to handle user input
************************************************************/

#include "InputManager.h"

using namespace sf;

namespace in {

	//^~^FUNCTIONS^~^//

		//Sets the control scheme//
	void InputManager::setControlType(ControlType inputControl, StateType currentState) {
		input = inputControl;

		switch (input) {
			case KMControl:		controller = new KeyboardMouse();		break;
			case GPControl:		controller = new Gamepad();				break;
			default:			controller = new KeyboardMouse();		break;
		}

			//Map input to game event
		controller->bindInput(currentState);	
	}

		//Handles user input//
	void InputManager::handleInput(RenderWindow* gameWindow, EntityManager* gameEntities, EventManager* eventMan, StateType currentState) {
	
		//Handle real-time controller input
		controller->handleEvents(eventMan, gameWindow, currentState);
		controller->handleInput(eventMan, currentState);
		
		//Execute queued events
		controller->execute(gameEntities, gameWindow, eventMan);
	}
}