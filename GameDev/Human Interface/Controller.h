/*******************************************************************
Class: Controller
File Type: h
Author: George Tranter
Description: Abstract class to represent a generic game controller
*******************************************************************/

#pragma once

#include "EventManager.h"
#include <string>

using namespace std;

class Controller {
	protected:

	public:
		//Loads input file, binds input to event
		virtual void bindInput(StateType) = 0;

		//Converts input event to a game event
		virtual void handleInput(EventManager*, StateType) = 0;

		virtual void handleEvents(EventManager*, RenderWindow*, StateType) = 0;

		//Executes queued events
		virtual void execute(EntityManager*, RenderWindow*, EventManager*) = 0;
};