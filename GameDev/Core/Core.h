/***********************************************************************
Class: Core
File Type: h
Author: George Tranter
Description: Class to be used as an encapsulation for the sub-systems
***********************************************************************/

#pragma once

#include "State.h"

class Core {

	private:
		State* gameState;

	public:
		Core();
		~Core();

		void ini(RenderWindow*);
		void update();
		void shutdown();
};