/************************************************************
Class: InputManager
File Type: h
Author: George Tranter
Description: Class to handle user input
************************************************************/

#pragma once

#include <SFML\Window.hpp>
#include "KeyboardMouse.h"
#include "Gamepad.h"

//Control schemes
enum ControlType{ KMControl = 0, GPControl};

namespace in {
	class InputManager {

		private:
			ControlType input;
			Controller* controller;

		public:
			void setControlType(ControlType, StateType);
			void handleInput(RenderWindow*, EntityManager*, EventManager*, StateType);
	};
}
