/************************************************************
Class: EventManager
File Type: cpp
Author: George Tranter
Description: Class to handle events with game logic
************************************************************/

#include "EventManager.h"

//^~^FUNCTIONS^~^//

	//Adds an event to the execution queue//
void EventManager::addEvent(EventNames e) {
	eventsToDo.push(e);
}

	//Executes events in the queue//
void EventManager::executeEvents(EntityManager* entities, RenderWindow* gameWindow) {
	while (eventsToDo.size() != 0) {

		switch (eventsToDo.front()) {
			case GoRight:			entities->getPlayer()->goRight();					break;
			case GoLeft:			entities->getPlayer()->goLeft();					break;
			case LightAttack:		entities->getPlayer()->lightAttack();				break;
			case Exit:				gameWindow->close();								break;
			case Pause:				isPaused = true; checkedPause = false;				break;
			case GameStart:			startGame = true;									break;
			case PlayerDamaged:		gameAudio->queueSound(PDamageSound);				break;

			case LevelComplete:
				levelComplete = true;
				addEvent(Despawn);
				break;

			case MenuReturn:	
				startGame = false;	
				addEvent(Despawn);
				break;

			case Jump:		
				if (entities->getPlayer()->getCanJump()) {
					entities->getPlayer()->jump();
					gameAudio->queueSound(JumpSound);
				}					
				break;

			case Despawn:			
				entities->enemyDespawn();
				toRespawn = true;
				checkedRespawn = false;
				break;

			case Spawn:				
				entities->enemySpawn();				
				spawnEnemies = true;
				break;

		}

		eventsToDo.pop();
	}

	eventsToDo.empty();
}