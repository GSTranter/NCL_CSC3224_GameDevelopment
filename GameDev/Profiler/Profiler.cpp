/***********************************************************************
Class: Profiler
File Type: cpp
Author: George Tranter
Description: Class to provide information on sub-system execution
***********************************************************************/

#include "Profiler.h"

//View how many frames per second
void Profiler::update() {
	frameCounter++;
	if (frameCounter == frameRate) {
		std::cout << std::endl << frameCounter << " updates in " << timer.getElapsedTime().asMilliseconds() << "ms" << std::endl;
		frameCounter = 0;
		timer.restart();
	}
	
}

//Return the execution time of a sub-system
void Profiler::systemTest(Subsystem subsystem, sf::Clock sysTimer) {
	if (frameCounter == frameRate - 1) {
		switch (subsystem) {
			case InputSys:				std::cout << std::endl << "Input";			break;
			case PhysicsSys:			std::cout << std::endl << "Physics";		break;
			case EntitySys:				std::cout << std::endl << "Entity";			break;
			case RenderSys:				std::cout << std::endl << "Render";			break;
			case AudioSys:				std::cout << std::endl << "Audio";			break;
		}

		std::cout << std::endl << " execution time in 60 frames: " << sysTimer.getElapsedTime().asMilliseconds() << "ms";
	}
}