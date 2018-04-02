/************************************************************
Class: Renderer
File Type: h
Author: George Tranter
Description: Class to be used as a render sub-system
************************************************************/

#pragma once

#include "EntityManager.h"
#include "TextureManager.h"

using namespace sf;

namespace rend {
	class Renderer {

		private:
			Sprite* background;
			Sprite* loading;
			Sprite* pauseOverlay;
			Sprite* gameOverOverlay;
			Sprite* victory;

			EntityManager* gameEntities;
			RenderWindow* gameWindow;
			TextureManager* stateTextures;

			//TODO
			bool platforms;
			bool enemies;

		public:
			Renderer();
			~Renderer();

			inline void setEntities(EntityManager* entities) { gameEntities = entities; }
			inline void setWindow(RenderWindow* window) { gameWindow = window; }

			void bindLevelTextures(string);
			void bindMenuTextures(string);

			void inGameRender(sf::Text*);
			void pauseGameRender();
			void gameOverRender();
			void menuRender();
			void loadingRender();
			void victoryRender();
	};
}