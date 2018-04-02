/************************************************************
Class: Player
File Type: h
Author: George Tranter
Description: Class to represent an enemy entity
************************************************************/

#pragma once
#include "Player.h"

class Enemy : public Entity, public Sprite {
	private:
		sf::Vector2f originalPos;
		void moveToPlayer(Player*);

		float health;
		float speed;
		float damage;
	public:
		//Getters and Setters
		void setStats(float, float, float);
		inline void setId(int inId) { id = inId; }
		inline float getDamage() { return damage; }
		void setOriginalPos(float, float);
		inline sf::Vector2f getOriginalPos() { return originalPos; }

		//Update where the enemy wants to go
		void enemyUpdate(Player*);
};