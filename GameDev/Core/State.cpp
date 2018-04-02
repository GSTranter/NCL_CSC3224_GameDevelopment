/***********************************************************************
Class: State
File Type: cpp
Author: George Tranter
Description: Class to represent a game state
***********************************************************************/

#include "State.h"

void State::iniState() {
	//Allocate resources
	gameResources = new ResourceManager();
	gameAudio = new Audio();
	eventMan = new EventManager();
	gameLogic = new GameLogic();
	gameResources->allocateResources(gameEntities, gameRenderer, gameInput, gamePhysics);

	//Set renderer parameters
	gameRenderer->setWindow(gameWindow);
	gameRenderer->setEntities(gameEntities);

	//Set-up event management
	eventMan->setAudioEvents(gameAudio);
	eventMan->setStartGame(false);
}

void State::shutdownState() {
	//Shutdown
	gameResources->deallocateReources();
	gameAudio->shutdownAudio();
	delete eventMan;
	delete gameLogic;
	delete gameAudio;
	delete gameResources;
	delete gameWindow;
}

void State::loadState(StateType currentState) {
	state = currentState;

	//Load the current state files
	switch (state) {
		case InGame:		loadLevel(currentLevel);		break;
		case Menu:			loadMenu();						break;
	}

	//Set control scheme
	gameInput->setControlType(KMControl, state);

	switch (state) {
		case InGame:
				//Entity ini
			gameEntities->inGameIni(getFile(PlayerFile), getFile(PlatformFile), getFile(EnemyFile));
				//Renderer texture binding
			gameRenderer->bindLevelTextures(getFile(TextureFile));
				//Physics ini
			gamePhysics->physicsIni(gameEntities, getFile(PhysicsFile), eventMan);
				//Audio ini
			gameAudio->inGameAudioIni(stateFiles[AudioFile]);
			break;

		case Menu:
				//Renderer texture binding
			gameRenderer->bindMenuTextures(getFile(TextureFile));
				//Audio ini
			gameAudio->menuAudioIni(stateFiles[AudioFile]);
			break;
	}


}

//Load a level given the number of the level
void State::loadLevel(int levelNum) {
	input_state inState;
	inState = FileInput::loadStateFiles("../Resources/Files/States/Level States/level" + std::to_string(levelNum) + ".txt");

	stateFiles[PlayerFile] = inState.playerFile;
	stateFiles[PlatformFile] = inState.platformFile;
	stateFiles[EnemyFile] = inState.enemyFile;
	stateFiles[TextureFile] = inState.textureFile;
	stateFiles[PhysicsFile] = inState.physicsFile;
	stateFiles[AudioFile] = inState.audioFile;
	stateFiles[LevelFile] = inState.levelFile;

	//Game Logic
	gameLogic->setUpWinCondi(stateFiles[LevelFile], eventMan);
	eventMan->setLevelComplete(false);
	eventMan->setRespawned();
	eventMan->setSpawnEnemies(false);
}

//Loads a menu image
void State::loadMenu() {
	input_state inState;
	inState = FileInput::loadStateFiles("../Resources/Files/States/menu.txt");
	
	stateFiles[TextureFile] = inState.textureFile;
	stateFiles[AudioFile] = inState.audioFile;

	currentLevel = 1;
}

	//Game pause state
void State::pauseState() {
	state = GamePause;
	//Set controls and events to pause state
	eventMan->setPauseCheck();
	gameInput->setControlType(KMControl, state);

	//Pause music and play pause sound
	gameAudio->getBgm()->pause();
	gameAudio->queueSound(PauseSound);
}

	//Ingame state : unpause
void State::unpauseState() {
	state = InGame;
	//Set controls and events to play state
	eventMan->setPauseCheck();
	gameInput->setControlType(KMControl, state);

	//Play music and play pause sound
	gameAudio->getBgm()->play();
	gameAudio->queueSound(PauseSound);
}

//Handle input update
void State::input() {
	sysTimer.restart();
	gameInput->handleInput(gameWindow, gameEntities, eventMan, state);
	if (profile) gameProfiler.systemTest(InputSys, sysTimer);
}

//Handle render update
void State::render() {
	sysTimer.restart();
	switch (state) {
		case InGame:		gameRenderer->inGameRender(gameLogic->getText());		break;
		case GamePause:		gameRenderer->pauseGameRender();						break;
		case Menu:			gameRenderer->menuRender();								break;
		case GameOver:		gameRenderer->gameOverRender();							break;
		case Victory:		gameRenderer->victoryRender();							break;
	}
	if (profile) gameProfiler.systemTest(RenderSys, sysTimer);
}

//Handle audio update
void State::audio() {
	sysTimer.restart();
	gameAudio->executeSounds();
	if (profile) gameProfiler.systemTest(AudioSys, sysTimer);
}

//Handle physics update
void State::physics() {
	sysTimer.restart();
	switch (state) {
		case InGame:		gamePhysics->physicsUpdate();		break; 
		case Menu:												break;
	}
	if (profile) gameProfiler.systemTest(PhysicsSys, sysTimer);
}

//Set gameover state
void State::gameOver() {
	state = GameOver;
	gameInput->setControlType(KMControl, state);

	gameAudio->getBgm()->stop();
	gameAudio->queueSound(PDeathSound);
}

//Set gamewon state
void State::victory() {
	state = Victory;
	gameInput->setControlType(KMControl, state);

	gameAudio->getBgm()->stop();
}

//Set ingame state : respawn
void State::respawn() {
	state = InGame;
	gameInput->setControlType(KMControl, state);
	gameAudio->getBgm()->play();
	gameEntities->getPlayer()->respawn();
	gamePhysics->physicsIni(gameEntities, getFile(PhysicsFile), eventMan);
}

//Check for transition
void State::checkState() {
	
	if (state == InGame && !eventMan->getPauseCheck() && eventMan->getPause()) {
		pauseState();
		gameLogic->pauseTime();
	}

	if (state == GamePause && !eventMan->getPauseCheck() &&  eventMan->getPause()) {
		unpauseState();
		gameLogic->resumeTime();
	}

	if (state == InGame && gameEntities->getPlayer()->isDead()) {
		gameOver();
	}

	if (state == GameOver && eventMan->getRespawned()) {
		eventMan->setRespawned();
		gameLogic->restartTime();
		respawn();
	}

	if (state == Menu && eventMan->getStartGame()) {
		gameRenderer->loadingRender();
		loadState(InGame);
	}

	if (state != Menu && !eventMan->getStartGame()) {
		gameRenderer->loadingRender();
		loadState(Menu);
	}

	if (state == InGame && eventMan->getSpawnEnemies()) {
		gameLogic->startTime();
		eventMan->setSpawnEnemies(false);
	}

	if (state == InGame && eventMan->getLevelComplete() && !gameLogic->getFinalLevel()) {
		currentLevel++;
		loadState(InGame);
	}

	if (state == InGame && eventMan->getLevelComplete() && gameLogic->getFinalLevel()) {
		currentLevel = 1;
		victory();
	}

}

//Update game entities based on game state
void State::entitiesUpdate() {
	sysTimer.getElapsedTime();
	switch (state) {
		case InGame:		gameEntities->inGameUpdate();	break;
		case GamePause:										break;
		case Menu:											break;
	}
	if (profile) gameProfiler.systemTest(EntitySys, sysTimer);
}

//Check if profiler is ready for output
void State::profilerCheck() {
	gameProfiler.update();
}

void State::logic() {
	switch (state) {
		case InGame:		gameLogic->checkTime();			break;
		case GamePause:										break;
		case Menu:											break;
	}
}