/************************************************************
Class: Phyiscs
File Type: cpp
Author: George Tranter
Description: Class to provide physics
************************************************************/

#include "Physics.h"
#include <iostream>

//Set up physics bodies for player and platforms
void Physics::setUpPlayPlat() {
	//Setup player
	//Position and body type
	b2BodyDef playerDef;
	playerDef.position = b2Vec2(gameEntities->getPlayer()->getPosition().x / PHYSICS_SCALE, gameEntities->getPlayer()->getPosition().y / PHYSICS_SCALE);
	playerDef.type = b2_dynamicBody;

	gameEntities->getPlayer()->getBody() = gameWorld->CreateBody(&playerDef);
	//Rotation
	gameEntities->getPlayer()->getBody()->SetFixedRotation(true);

	//Body shape
	b2PolygonShape playerBox;
	playerBox.SetAsBox((gameEntities->getPlayer()->getGlobalBounds().width / SIZE_MULT) / PHYSICS_SCALE, (gameEntities->getPlayer()->getGlobalBounds().height / SIZE_MULT) / PHYSICS_SCALE);	//Size

	//Physics values
	b2FixtureDef playerFixture; 
	playerFixture.density = inPhysics.playerDens;
	playerFixture.friction = inPhysics.playerFric;
	playerFixture.shape = &playerBox;

	gameEntities->getPlayer()->getBody()->CreateFixture(&playerFixture);

	//ID set up
	playerId = gameEntities->getPlayer()->getId();
	int* playerIdPoint = &playerId;
	gameEntities->getPlayer()->getBody()->SetUserData(playerIdPoint);
	//Player done

	//Setup platforms
	for (int i = 0; i < gameEntities->getNumPlatforms(); i++) {
		//Position and body type
		b2BodyDef platformDef;
		platformDef.position = b2Vec2((gameEntities->getPlatform(i)->getPosition().x + ((gameEntities->getPlatform(i)->getSize().x + SIZE_ADD) / SIZE_MULT)) / PHYSICS_SCALE, 
									  (gameEntities->getPlatform(i)->getPosition().y + ((gameEntities->getPlatform(i)->getSize().y + SIZE_ADD) / SIZE_MULT)) /  PHYSICS_SCALE);
		platformDef.type = b2_staticBody;

		gameEntities->getPlatform(i)->getBody() = gameWorld->CreateBody(&platformDef);

		//body shape
		b2PolygonShape platformBox;
		platformBox.SetAsBox((gameEntities->getPlatform(i)->getSize().x / SIZE_MULT) / PHYSICS_SCALE, (gameEntities->getPlatform(i)->getSize().y / SIZE_MULT) / PHYSICS_SCALE);

		//Physics and collision values
		b2FixtureDef platformFixture;
		platformFixture.filter.categoryBits = 0x0002;
		platformFixture.density = inPhysics.platformDens;
		platformFixture.shape = &platformBox;
		gameEntities->getPlatform(i)->getBody()->CreateFixture(&platformFixture);
		
		//ID set up
		platformId = gameEntities->getPlatform(i)->getId();
		int* platformIdPoint = &platformId;
		gameEntities->getPlatform(i)->getBody()->SetUserData(platformIdPoint);
	}
	//Platforms done

}

//Setup enemies
void Physics::setUpEnemies() {
	for (int i = 0; i < gameEntities->getNumEnemies(); i++) {
		//Position and body type
		b2BodyDef enemyDef;
		enemyDef.position = b2Vec2(gameEntities->getEnemy(i)->getPosition().x / PHYSICS_SCALE, gameEntities->getEnemy(i)->getPosition().y / PHYSICS_SCALE);
		enemyDef.type = b2_dynamicBody;

		gameEntities->getEnemy(i)->getBody() = gameWorld->CreateBody(&enemyDef);
		//Rotation
		gameEntities->getEnemy(i)->getBody()->SetFixedRotation(true);

		//Body shape
		b2PolygonShape enemyBox;
		enemyBox.SetAsBox((gameEntities->getEnemy(i)->getGlobalBounds().width / SIZE_MULT) / PHYSICS_SCALE, (gameEntities->getEnemy(i)->getGlobalBounds().height / SIZE_MULT) / PHYSICS_SCALE);

		//Physics and collision values
		b2FixtureDef enemyFixture;
		enemyFixture.filter.maskBits = 0x0001;
		enemyFixture.density = inPhysics.enemyDens;
		enemyFixture.restitution = inPhysics.enemyBounce;
		enemyFixture.shape = &enemyBox;

		gameEntities->getEnemy(i)->getBody()->SetGravityScale(0.f);
		gameEntities->getEnemy(i)->getBody()->CreateFixture(&enemyFixture);

		//ID set up
		enemyId = gameEntities->getEnemy(i)->getId();
		int* enemyIdPoint = &enemyId;
		gameEntities->getEnemy(i)->getBody()->SetUserData(enemyIdPoint);
	}
}

//Load in physics file and set up entities
void Physics::physicsIni(EntityManager* entities, string physicsFile, EventManager* eventMan) {
	gameEntities = entities;

	inPhysics = FileInput::loadStatePhysics(physicsFile);

	EnemyPlayerListener* listener = new EnemyPlayerListener();
	
	b2Vec2 gravity(0.0f, inPhysics.gravity);
	gameWorld = new b2World(gravity);

	listener->listenerIni(entities, eventMan);
	gameWorld->SetContactListener(listener);

	gameEntities->setPhysics(false);

	setUpPlayPlat();
}

//Update physics
void Physics::physicsUpdate() {
	gameWorld->Step(1 / FRAMES, VEL_ITS, POS_ITS);

	//Set up enemy bodies if they're spawned
	if (gameEntities->getSpawned() == true && gameEntities->isPhysicsSet() == false) {
		setUpEnemies();
		gameEntities->setPhysics(true);
	}

	//Destroy enemy bodies if they're despawned
	if (gameEntities->getSpawned() == false && gameEntities->isPhysicsSet() == true) {
		for (int i = 0; i < gameEntities->getNumEnemies(); i++) {
			gameWorld->DestroyBody(gameEntities->getEnemy(i)->getBody());
		}
		gameEntities->setPhysics(false);
	}
	
}
