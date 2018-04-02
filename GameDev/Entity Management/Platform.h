/************************************************************
Class: Platform
File Type: h
Author: George Tranter
Description: Class to represent a game platform
************************************************************/

#pragma once

#include "Entity.h"

class Platform : public Entity, public RectangleShape {
	protected:
		float speedMod;

	public:
		Platform();
		~Platform();
};