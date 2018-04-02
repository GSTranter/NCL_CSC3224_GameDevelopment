/************************************************************
Class: Entity
File Type: h
Author: George Tranter
Description: Class to represent a generic entity
************************************************************/

#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <fstream>
#include <sstream>

#define PHYSICS_SCALE 30
//Game states for use throughout the engine
enum StateType { Menu = 0, InGame, GamePause, GameOver, Victory };

using namespace sf;

class Entity{

	protected:
		bool vertRest = true;
		int vertRestSteps = 0;
		bool horzRest = true;
		int horzRestSteps = 0;
		int id = 0;

		b2Body* physicsBody;

	public:
		Entity();
		virtual ~Entity();

		inline b2Body*& getBody() {return physicsBody;}
		inline int getId() { return id; }
};

