#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "FileInput.h"
#include "EventManager.h"

class GameLogic {
	private:
		EventManager* gameEvents;

		sf::Clock winTimer;
		float levelTime;
		float currentTime;
		float timeLeft;

		bool start;
		bool wantText;
		bool finalLevel;

		sf::Font* font;
		sf::Text* text;

		std::string preText;
		std::string duringText;
		std::string postText;
	public:
		inline sf::Text* getText() { return text; }
		inline bool getFinalLevel() { return finalLevel; }

		void setUpWinCondi(string, EventManager*);
		void startTime();
		void restartTime();
		void checkTime();
		void pauseTime();
		void resumeTime();
};