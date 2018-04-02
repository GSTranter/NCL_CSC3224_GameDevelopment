/***********************************************************************
Class: Profiler
File Type: h
Author: George Tranter
Description: Class to provide information on sub-system execution
***********************************************************************/

#pragma once

#include <SFML\System.hpp>
#include <iostream>

enum Subsystem { InputSys = 0, PhysicsSys, EntitySys, RenderSys, AudioSys};

class Profiler {
	private:
		const int frameRate = 60;
		int frameCounter;
		sf::Clock timer;
	public:
		void update();
		void systemTest(Subsystem, sf::Clock);
};
