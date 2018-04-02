/***********************************************************************
Class: Core
File Type: cpp
Author: George Tranter
Description: Class to be used as an encapsulation for the sub-systems
***********************************************************************/

#include "Core.h"

//^~^CONSTRUCTOR^~^//
Core::Core() {}
Core::~Core() {};

//^~^FUNCTIONS^~^//

	//Game initialisation//
void Core::ini(RenderWindow* window) {
	gameState = new State();
	gameState->setWindow(window);
	gameState->iniState();

	//Game state
	gameState->loadState(Menu);
}
	
	//Game loop//
void Core::update(){
	gameState->input();
	gameState->checkState();
	gameState->physics();
	gameState->physics();
	gameState->entitiesUpdate();
	gameState->logic();
	gameState->render();
	gameState->audio();
	if(gameState->profileStatus()) gameState->profilerCheck();
}

	//Game shutdown//
void Core::shutdown() {
	gameState->shutdownState();
	delete gameState;
}