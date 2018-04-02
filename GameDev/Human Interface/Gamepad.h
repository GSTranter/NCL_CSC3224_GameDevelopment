
#pragma once

#include "Controller.h"

class Gamepad : public Controller {
	private:
	public:
		void bindInput(StateType);
		void handleEvents(EventManager*, RenderWindow*, StateType);
		void handleInput(EventManager*, StateType);
		void execute(EntityManager*, RenderWindow*,EventManager*);
};