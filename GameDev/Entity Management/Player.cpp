/************************************************************
Class: Player
File Type: cpp
Author: George Tranter
Description: Class to represent a player entity
************************************************************/

#include "Player.h"
#include <iostream>

using namespace sf;

void Player::checkStatus() {
	//Checks for horizontal rest
	//If motionless for > 5 frames, at rest
	if (physicsBody->GetLinearVelocity().x == 0.f && horzRestSteps < 5) {
		horzRestSteps++;
	}
	if (physicsBody->GetLinearVelocity().x != 0.f) {
		horzRestSteps = 0;
		horzRest = false;
	}
	if (horzRestSteps == 5) {
		horzRest = true;
	}

	//Checks for vertical rest
	//If motionless for > 5 frames, at rest
	if (physicsBody->GetLinearVelocity().y == 0.f && vertRestSteps < 5) {
		vertRestSteps++;
	}
	if (physicsBody->GetLinearVelocity().y != 0.f) {
		vertRestSteps = 0;
		vertRest = false;
	}
	if (vertRestSteps == 5) {
		vertRest = true;
	}

	//Check if the player can jump
	if (vertRest == true) {
		canJump = true;
		

		if (goingLeft) {
			setTexture(*playerLeft);
		}
		else {
			setTexture(*playerRight);
		}
	}
	else {
		canJump = false;
	}

	//Check if the player can attack
	if (attackCD == attackSpeed) {
		canAttack = true;
	}
	else {
		attackCD++;
	}

	//Sleep if at vertical and horizontal rest
	if (horzRest == true && vertRest == true) {
		physicsBody->SetAwake(false);
	}
}

void Player::playerUpdate() {
	checkStatus();
	//If physics body is awake, calculate postion
	if (physicsBody->IsActive()) {
		setPosition(PHYSICS_SCALE * physicsBody->GetPosition().x, PHYSICS_SCALE * physicsBody->GetPosition().y);
	}

	if (getPosition().y > fallen) {
		currentHealth = 0;
	}

	//If health is below zero, then dead
	if (currentHealth <= 0) {
		dead = true;
	}
}

void Player::goRight() {
	//Apply right force
	physicsBody->ApplyForce(b2Vec2(speed, 0), physicsBody->GetWorldCenter(), true);
	
	//Set texture
	if (goingLeft) {
		setTexture(*playerRight);
		goingLeft = false;
	}
}

void Player::goLeft() {
	//Apply left force
	physicsBody->ApplyForce(b2Vec2(-speed, 0), physicsBody->GetWorldCenter(), true);
	
	//Set texture
	if (!goingLeft){
		setTexture(*playerLeft);
		goingLeft = true;
	}
}

void Player::jump() {
	//If player can jump, apply jump and set texture
	physicsBody->ApplyForce(b2Vec2(0, -jumpStrength), physicsBody->GetWorldCenter(), true);
	
	if (goingLeft) {
		setTexture(*playerJumpLeft);
	}
	else {
		setTexture(*playerJumpRight);
	}
}

//Check attack
void Player::lightAttack() {
	if (canAttack) {
		attackCD = 0;
		canAttack = false;
	}
}

//Take damage away from health
void Player::damaged(float damage) {
	currentHealth -= damage;
}

void Player::setStats(float inHP, float inSpeed, float inJump, float inDam, float inAtkSpd) {
	id = 1;
	maxHealth = inHP;
	currentHealth = maxHealth;
	speed = inSpeed;
	jumpStrength = inJump;
	damage = inDam;
	attackSpeed = inAtkSpd;
	attackCD = attackSpeed;
}

//Reset player death status
void Player::respawn() {
	dead = false;
	currentHealth = maxHealth;
	setPosition(originalPosition);
}

void Player::iniPosition(float xPos, float yPos) {
	originalPosition.x = xPos;
	originalPosition.y = yPos;
	setPosition(originalPosition);
}