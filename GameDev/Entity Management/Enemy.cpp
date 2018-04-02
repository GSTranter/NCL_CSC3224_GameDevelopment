/************************************************************
Class: Player
File Type: h
Author: George Tranter
Description: Class to represent an enemy entity
************************************************************/

#include "Enemy.h"
#include <iostream>

void Enemy::moveToPlayer(Player* gamePlayer) {
	//Find the vector between the enemy and player
	b2Vec2 betweenVec(gamePlayer->getBody()->GetPosition().x - physicsBody->GetPosition().x, gamePlayer->getBody()->GetPosition().y - physicsBody->GetPosition().y);

	//Find the unit vector and multiply by speed
	betweenVec.Normalize();
	betweenVec.x = betweenVec.x * speed;
	betweenVec.y = betweenVec.y * speed;

	physicsBody->SetLinearVelocity(betweenVec);
}

void Enemy::enemyUpdate(Player* gamePlayer) {

	//Update enemy position
	moveToPlayer(gamePlayer);
	setPosition(PHYSICS_SCALE * physicsBody->GetPosition().x, PHYSICS_SCALE * physicsBody->GetPosition().y);

}

void Enemy::setOriginalPos(float x, float y) {
	originalPos.x = x;
	originalPos.y = y;
}

void Enemy::setStats(float inhealth, float inspeed, float indamage) {
	id = 2;
	health = inhealth;
	speed = inspeed;
	damage = indamage;
}