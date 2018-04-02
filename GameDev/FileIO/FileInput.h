/************************************************************
Class: FileInput
File Type: h
Author: George Tranter
Description: Class to provide utility functions for
			 file input
************************************************************/

#pragma once

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//Texture
typedef struct {
	string name;
	string texFile;
}input_texture;

//Player
typedef struct {
	float xPos;
	float yPos;
	float health;
	float speed;
	float jumpStrength;
	float damage;
	float attackSpeed;
	float PAD;
}input_player;

//Enemy
typedef struct {
	float xPos;
	float yPos;
	float health;
	float speed;
	float damage;
	float PAD;
}input_enemy;

//Platform
typedef struct {
	float xPos;
	float yPos;
	float height;
	float width;
}input_platform;

//Physics
typedef struct {
	float gravity;
	float playerDens;
	float playerFric;
	float platformDens;
	float enemyDens;
	float enemyBounce;
}input_physics;

//State
typedef struct {
	string playerFile;
	string platformFile;
	string enemyFile;
	string textureFile;
	string physicsFile;
	string audioFile;
	string levelFile;
}input_state;

//Level meta text
typedef struct {
	float levelTime;
	bool wantText;
	bool lastLevel;
	string font;
	string pre;
	string during;
	string post;
}input_meta;

//Audio
typedef struct {
	string musicFile;
	string jumpFile;
	string pauseFile;
	string deathFile;
	string damageFile;
}input_audio;

class FileInput {
	
	public:
		//Load player
		static input_player	loadStatePlayer(string);
		//Load platforms
		static vector<input_platform> loadStatePlatforms(string);
		//Load phyics
		static input_physics loadStatePhysics(string);
		//Load enemies
		static vector<input_enemy> loadStateEnemies(string);
		//Load files
		static input_state loadStateFiles(string);
		//Load level data
		static input_meta loadLevelMeta(string);
		//Load audio
		static input_audio loadStateAudio(string);
};