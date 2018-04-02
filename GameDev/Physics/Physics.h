/************************************************************
Class: Phyiscs
File Type: h
Author: George Tranter
Description: Class to provide physics
************************************************************/

#pragma once
#include <sfml/Graphics.hpp>
#include <Box2D\Box2D.h>
#include "EntityManager.h"
#include "FileInput.h"
#include "EnemyPlayerListener.h"
#include "EventManager.h"

#define SIZE_MULT 2
#define SIZE_ADD -50
#define FRAMES 60.0f
#define VEL_ITS 8
#define POS_ITS 3


class Physics {
	private:
		b2World* gameWorld;
		EntityManager* gameEntities;

		input_physics inPhysics;

		void setUpPlayPlat();
		void setUpEnemies();

		int playerId;
		int platformId;
		int enemyId;
	public:
		void physicsIni(EntityManager*, string, EventManager*);
		void physicsUpdate();
};