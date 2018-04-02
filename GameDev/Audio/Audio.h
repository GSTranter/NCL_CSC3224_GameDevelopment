/***********************************************************************
Class: Audio
File Type: h
Author: George Tranter
Description: Class to provide audio for game states
***********************************************************************/

#pragma once

#include "FileInput.h"
#include <map>
#include <queue>
#include <SFML\Audio.hpp>

using namespace sf;

//Enum to detail audio events
enum AudioEvent { JumpSound = 0, PauseSound, PDeathSound, PDamageSound};

class Audio {
	private:
		Music* bgm;
		map<AudioEvent, Sound> gameSounds;
		queue<AudioEvent> soundsToPlay;

			//Keeps any sound buffers in scope
		SoundBuffer* soundBuffers[4];
		input_audio currentFiles;
		
	public:
		inline Music* getBgm() { return bgm; }

		//Initialise 
		void inGameAudioIni(string);
		void menuAudioIni(string);

		//Add game sound to the queue
		void queueSound(AudioEvent);

		//Execute the sounds on the queue
		void executeSounds();

		void shutdownAudio();
};