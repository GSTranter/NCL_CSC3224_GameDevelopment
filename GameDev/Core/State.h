/***********************************************************************
Class: State
File Type: h
Author: George Tranter
Description: Class to represent a game state
***********************************************************************/

#pragma once
#include <string>
#include <map>
#include "FileInput.h"
#include "Resource Manager.h"
#include "Physics.h"
#include "Audio.h"
#include "Profiler.h"
#include "GameLogic.h"

using namespace std;

//Enum to describe the different files to load in data
enum FileType{ PlayerFile = 0, PlatformFile, EnemyFile, TextureFile, PhysicsFile, AudioFile, LevelFile};

class State {
	private:
		const bool profile = false;
		int currentLevel;
		sf::Clock sysTimer;

		StateType state;
		map<FileType, std::string> stateFiles;

		Profiler gameProfiler;
		//State subsystems
		ResourceManager* gameResources;
		RenderWindow* gameWindow;
		EntityManager* gameEntities;
		rend::Renderer* gameRenderer;
		in::InputManager* gameInput;
		Physics* gamePhysics;
		EventManager* eventMan;
		Audio* gameAudio;
		GameLogic* gameLogic;


	public:
		//Getters and setters
		inline void setWindow(RenderWindow* window) { gameWindow = window; }
		inline string getFile(FileType file) { return stateFiles[file]; }
		inline RenderWindow* getWindow() { return gameWindow; }
		inline EntityManager* getEntities() { return gameEntities; } 
		inline rend::Renderer* getRenderer() { return gameRenderer; }
		inline in::InputManager* getGameInput() { return gameInput; }
		inline Physics* getPhysics() { return gamePhysics; }
		inline EventManager* getEventMan() { return eventMan; }
		inline bool profileStatus() { return profile; }

		//Initialise state functions
		void iniState();
		void loadState(StateType);
		void loadLevel(int);
		void loadMenu();

		//Specified state changes
		void pauseState();
		void unpauseState();
		void gameOver();
		void respawn();
		void victory();

		//Loop update methods
		void input();
		void checkState();
		void entitiesUpdate();
		void profilerCheck();
		void physics();
		void render();
		void audio();
		void logic();

		void shutdownState();
};