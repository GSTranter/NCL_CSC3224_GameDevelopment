/************************************************************
Class: Projectile
File Type: h
Author: George Tranter
Description: Class to represent a projectile
************************************************************/

#pragma once
#include "Entity.h"
class Projectile : public Entity, public sf::Sprite {
	private:
		float lifetime;
		bool newProjectile;
	public:
		inline float getLifetime() { return lifetime; }
		inline bool isNew() { return newProjectile; }
		inline void setNew(bool newProj) { newProjectile = newProj; }
};