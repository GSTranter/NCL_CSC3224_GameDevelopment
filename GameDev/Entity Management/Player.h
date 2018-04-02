/************************************************************
Class: Player
File Type: h
Author: George Tranter
Description: Class to represent a player entity
************************************************************/

#pragma once
#include "Entity.h"

using namespace sf;

class Player : public Entity , public Sprite{
	private:
		const int fallen = 720;

		//Player Textures
		sf::Texture* playerRight;
		sf::Texture* playerLeft;
		sf::Texture* playerJumpRight;
		sf::Texture* playerJumpLeft;
		
		//Player checks
		bool goingLeft;
		bool canJump;
		bool canAttack;
		bool dead;

		//Player stats
		float maxHealth;
		float currentHealth;
		float speed;
		float jumpStrength;
		float damage;
		int attackSpeed;
		int attackCD;
		sf::Vector2f originalPosition;

		void checkStatus();
	public:

		//Getters and setters
		inline sf::Texture* getStartingTexture() { return playerRight; }
		inline void setRightTexture(sf::Texture* inputRight) { playerRight = inputRight; }
		inline void setLeftTexture(sf::Texture* inputLeft) { playerLeft = inputLeft; }
		inline void setJumpRightTexture(sf::Texture* inputJump) { playerJumpRight = inputJump;  }
		inline void setJumpLeftTexture(sf::Texture* inputJump) { playerJumpLeft = inputJump; }

		inline bool getCanJump() { return canJump; }
		inline bool isDead() { return dead; }

		void setStats(float,float,float,float,float);
		void iniPosition(float, float);

		//Update for game loop
		void playerUpdate();

		//Game logic events
		void goRight();
		void goLeft();
		void jump();
		void lightAttack();
		void damaged(float);
		void respawn();
};
