#include "GameLogic.h"

void GameLogic::setUpWinCondi(string fileName, EventManager* inEvents) {
	gameEvents = inEvents;

	input_meta levelData = FileInput::loadLevelMeta(fileName);
	levelTime = levelData.levelTime;
	wantText = levelData.wantText;
	finalLevel = levelData.lastLevel;
	preText = levelData.pre;
	duringText = levelData.during;
	postText = levelData.post;

	currentTime = levelTime;
	timeLeft = levelTime;
	start = false;
	
	if (wantText) {
		font = new sf::Font();
		if (!font->loadFromFile(levelData.font)) {
			printf("CAN'T LOAD FONT. TEXT WILL NOT BE DISPLAYED");
		}

		text = new sf::Text();
		std::string textString = preText + "\nTime Remaining: " + std::to_string(levelTime);
		text->setFont(*font);
		text->setString(textString);
		text->setCharacterSize(12);
		text->setFillColor(sf::Color::Black);
		text->setPosition(0, 20);
	}
}

void GameLogic::checkTime() {
	if (start && timeLeft > 0) {
		timeLeft = currentTime - winTimer.getElapsedTime().asSeconds();
		if (wantText) {
			std::string textString = duringText + "\nTime Remaining: " + std::to_string(timeLeft);
			text->setString(textString);
		}
	}

	if (timeLeft <= 0) {
		timeLeft = 0;
		gameEvents->addEvent(LevelComplete);
		if (wantText) {
			std::string textString = postText + "\nTime Remaining: " + std::to_string(timeLeft);
			text->setString(textString);
		}
	}
	

}

void GameLogic::startTime() {
	if (!start) {
		start = true;
		winTimer.restart();
	}
}

void GameLogic::restartTime() {
	start = false;
	currentTime = levelTime;
	if (wantText) {
		std::string textString = preText + "\nTime Remaining: " + std::to_string(levelTime);
		text->setString(textString);
	}
}

void GameLogic::pauseTime() {
	currentTime = timeLeft;
}

void GameLogic::resumeTime() {
	winTimer.restart();
}