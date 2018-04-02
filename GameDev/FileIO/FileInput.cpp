/************************************************************
Class: FileInput
File Type: h
Author: George Tranter
Description: Class to provide utility functions for
file input
************************************************************/

#include "FileInput.h"
#include <iostream>

//Load player
input_player FileInput::loadStatePlayer(string fileName) {
	ifstream inputFile(fileName);
	string line;
	getline(inputFile, line);
	istringstream inLine(line);

	input_player player;
	inLine >> player.xPos >> player.yPos >> player.health >> player.speed >> player.jumpStrength >> player.damage >> player.attackSpeed;

	return player;
}

//Load state files
input_state FileInput::loadStateFiles(string fileName) {
	ifstream inputFile(fileName);
	string line;
	getline(inputFile, line);
	istringstream inLine(line);

	input_state state;
	inLine >> state.playerFile >> state.platformFile >> state.enemyFile >> state.textureFile >> state.physicsFile >> state.audioFile >> state.levelFile;
	return state;
}

//Load level game logic
input_meta FileInput::loadLevelMeta(string fileName) {
	ifstream inputFile(fileName);
	string line;
	getline(inputFile, line);
	istringstream inLine(line);

	input_meta level;
	inLine >> level.levelTime >> level.wantText >> level.lastLevel >> level.font >> level.pre >> level.during >> level.post;
	return level;
}

//Load physics
input_physics FileInput::loadStatePhysics(string fileName) {
	ifstream inputFile(fileName);
	string line;
	getline(inputFile, line);
	istringstream inLine(line);

	input_physics physics;
	inLine >> physics.gravity >> physics.playerDens >> physics.playerFric >> physics.platformDens >> physics.enemyDens >> physics.enemyBounce;
	return physics;
}

//Load platforms
vector<input_platform> FileInput::loadStatePlatforms(string fileName){
	ifstream inputFile(fileName);
	vector<input_platform> platformReturn;

	for (string line; getline(inputFile, line);) {
		istringstream inLine(line);
		input_platform platformBuff;

		inLine >> platformBuff.xPos >> platformBuff.yPos >> platformBuff.height >> platformBuff.width;
		platformReturn.push_back(platformBuff);
	}

	return platformReturn;
}

//Load enemies
vector<input_enemy> FileInput::loadStateEnemies(string fileName) {
	ifstream inputFile(fileName);
	vector<input_enemy> enemyReturn;

	for (string line; getline(inputFile, line);) {
		istringstream inLine(line);
		input_enemy enemyBuff;

		inLine >> enemyBuff.xPos >> enemyBuff.yPos >> enemyBuff.health >> enemyBuff.speed >> enemyBuff.damage;
		enemyReturn.push_back(enemyBuff);
	}

	return enemyReturn;
}

//Load Audio
input_audio FileInput::loadStateAudio(string fileName) {
	ifstream inputFile(fileName);
	string line;
	getline(inputFile, line);
	istringstream inLine(line);

	input_audio audio;
	inLine >> audio.musicFile >> audio.jumpFile >> audio.pauseFile >> audio.deathFile >> audio.damageFile;
	return audio;
}
