#include "SoundEffect.h"
#include "Errors.h"

SoundEffect::SoundEffect(std::string id, char fileName[]){
	setID(id);
	setSound(fileName);	
}

SoundEffect::~SoundEffect(){
}

void SoundEffect::setID(std::string _id) {
	id = _id;
}

void SoundEffect::setSound(char fileName[]) {
	sound = Mix_LoadWAV(fileName);
	if (sound == NULL) {
		fatalError("Failed to load sound effect! SDL_mixer Error: %s\n" + std::string(fileName));
	}
}

std::string SoundEffect::getID() {
	return id;
}

