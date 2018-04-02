/***********************************************************************
Class: Audio
File Type: cpp
Author: George Tranter
Description: Class to provide audio for game states
***********************************************************************/

#include "Audio.h"
#include <iostream>

void Audio::inGameAudioIni(string fileName) {
	//Load audio file
	input_audio inAudio = FileInput::loadStateAudio(fileName);

	if (inAudio.jumpFile != currentFiles.jumpFile) {
		//Load jump sound
		soundBuffers[0] = new SoundBuffer();
		if (!inAudio.jumpFile.empty()) {
			soundBuffers[0]->loadFromFile(inAudio.jumpFile);
			gameSounds[JumpSound] = Sound(*soundBuffers[0]);
		}

		currentFiles.jumpFile = inAudio.jumpFile;
	}

	if (inAudio.pauseFile != currentFiles.pauseFile) {
		//Load pause sound
		soundBuffers[1] = new SoundBuffer();
		if (!inAudio.pauseFile.empty()) {
			soundBuffers[1]->loadFromFile(inAudio.pauseFile);
			gameSounds[PauseSound] = Sound(*soundBuffers[1]);
		}

		currentFiles.pauseFile = inAudio.pauseFile;
	}
	
	if (inAudio.deathFile != currentFiles.deathFile) {
		//Load death sound
		soundBuffers[2] = new SoundBuffer();
		if (!inAudio.deathFile.empty()) {
			soundBuffers[2]->loadFromFile(inAudio.deathFile);
			gameSounds[PDeathSound] = Sound(*soundBuffers[2]);
		}

		currentFiles.deathFile = inAudio.deathFile;
	}
	
	if (inAudio.damageFile != currentFiles.damageFile) {
		//Load damage sound
		soundBuffers[3] = new SoundBuffer();
		if (!inAudio.damageFile.empty()) {
			soundBuffers[3]->loadFromFile(inAudio.damageFile);
			gameSounds[PDamageSound] = Sound(*soundBuffers[3]);
		}

		currentFiles.damageFile = inAudio.damageFile;
	}
	
	//Play bgm
	if (inAudio.musicFile != currentFiles.musicFile) {
		currentFiles.musicFile = inAudio.musicFile;
		if (bgm != NULL) {
			delete bgm;
		}

		bgm = new Music;
		if (!inAudio.musicFile.empty()) {
			bgm->openFromFile(inAudio.musicFile);
			bgm->setVolume(50);
			bgm->setLoop(true);
			bgm->play();
		}
	}

}

void Audio::menuAudioIni(string fileName) {
	//Load BGM
	input_audio inAudio = FileInput::loadStateAudio(fileName);

	if (inAudio.musicFile != currentFiles.musicFile) {
		currentFiles.musicFile = inAudio.musicFile;
		//Play bgm
		if (bgm != NULL) {
			delete bgm;
		}
		bgm = new Music;
		if (!inAudio.musicFile.empty()) {
			bgm->stop();
			bgm->openFromFile(inAudio.musicFile);
			bgm->setLoop(true);
			bgm->play();
		}
	}
}

//Add sound to queue based on audio event
void Audio::queueSound(AudioEvent e) {
	soundsToPlay.push(e);
}

//Execute sounds on the queue
void Audio::executeSounds() {
	while (soundsToPlay.size() != 0) {
		gameSounds[soundsToPlay.front()].play();
		soundsToPlay.pop();
	}
}

void Audio::shutdownAudio() {
	delete bgm;
	for (int i = 0; i < 3; i++) {
		delete soundBuffers[i];
	}
}