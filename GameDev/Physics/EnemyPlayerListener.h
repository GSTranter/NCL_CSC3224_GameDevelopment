/************************************************************
Class: EnemyPlayerListener
File Type: h
Author: George Tranter
Description: Class to listen for enemy-player collisions
************************************************************/

#pragma once

#include <Box2D\Box2D.h>
#include "EventManager.h"
#include <iostream>

class EnemyPlayerListener : public b2ContactListener {
	private:
		EntityManager* gameEntities;
		EventManager* gameEvents;
	public:
		void listenerIni(EntityManager*, EventManager*);
		void BeginContact(b2Contact* contact);

};