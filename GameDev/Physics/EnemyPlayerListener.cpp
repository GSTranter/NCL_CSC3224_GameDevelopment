/************************************************************
Class: EnemyPlayerListener
File Type: h
Author: George Tranter
Description: Class to listen for enemy-player collisions
************************************************************/

#include "EnemyPlayerListener.h"

//Ini
void EnemyPlayerListener::listenerIni(EntityManager* inputEntities, EventManager* inputEventMan) {
	gameEntities = inputEntities;
	gameEvents = inputEventMan;
}

//Listens for enemy-player contact
void EnemyPlayerListener::BeginContact(b2Contact* contact) {
	int* bodyUserDataA = (int*)contact->GetFixtureA()->GetBody()->GetUserData();
	int* bodyUserDataB = (int*)contact->GetFixtureB()->GetBody()->GetUserData();

	//If the id is enemy-player or player-enemy
	if ((*bodyUserDataA == 1 && *bodyUserDataB >= 2) || (*bodyUserDataA >= 2 && *bodyUserDataB == 1)) {
		
		//Damage player based on damage of the enemy that was collided with
		if (*bodyUserDataA == 1) {
			gameEntities->getPlayer()->damaged(gameEntities->getEnemy(*bodyUserDataB - gameEntities->getEnemy(0)->getId())->getDamage());
			gameEvents->addEvent(PlayerDamaged);
		}
		else {
			gameEntities->getPlayer()->damaged(gameEntities->getEnemy(*bodyUserDataA - gameEntities->getEnemy(0)->getId())->getDamage());
			gameEvents->addEvent(PlayerDamaged);
		}
		
	}


}