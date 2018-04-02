/************************************************************
Class: EventManager
File Type: h
Author: George Tranter
Description: Class to handle events with game logic
************************************************************/

#pragma once

#include <SFML\Graphics.hpp>
#include <queue>
#include "EntityManager.h"
#include "Audio.h"

//Names of in-game, player activated events
enum EventNames { GoLeft = 1, GoRight, Jump, LightAttack, HeavyAttack, Dodge, Pause, Exit, Spawn, Despawn, GameStart, MenuReturn, PlayerDamaged, LevelComplete };

class EventManager {
	private:
		std::queue<EventNames> eventsToDo;
		Audio* gameAudio;

		bool isPaused;
		bool checkedPause;
		bool toRespawn;
		bool checkedRespawn;
		bool spawnEnemies;

		bool startGame;

		bool levelComplete;
	public:

		//Getters and setters
		inline bool getPause() { return isPaused; }
		inline bool getPauseCheck() { return checkedPause; }
		inline void setPauseCheck() { checkedPause = true; }
		inline bool getRespawned() { return toRespawn; }
		inline bool getRespawnCheck() { return checkedRespawn; }
		inline void setRespawned() { toRespawn = false; }
		inline bool getSpawnEnemies() { return spawnEnemies; }
		inline void setSpawnEnemies(bool spawn) { spawnEnemies = spawn; }

		inline bool getStartGame() { return startGame; }
		inline void setStartGame(bool game) { startGame = game; }

		inline bool getLevelComplete() { return levelComplete; }
		inline void setLevelComplete(bool done) { levelComplete = done; }

		//Ini
		inline void setAudioEvents(Audio* inAudio) { gameAudio = inAudio; }
		
		//Runtime
		void addEvent(EventNames);
		void executeEvents(EntityManager*, RenderWindow*);
};