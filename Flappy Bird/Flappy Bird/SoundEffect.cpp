#include "SoundEffect.h"
#include "Errors.h"

// constructor
SoundEffect::SoundEffect(std::string id, char fileName[]){
	setID(id);
	setSound(fileName);	
}

// destructor
SoundEffect::~SoundEffect(){
	sound = NULL;
}

// sets the id of the sound
void SoundEffect::setID(std::string _id) {
	id = _id;
}

// sets the sound object from filepath
void SoundEffect::setSound(char fileName[]) {
	sound = Mix_LoadWAV(fileName);
	if (sound == NULL) {
		fatalError("Failed to load sound effect! SDL_mixer Error: %s\n" + std::string(fileName));
	}
}

// returns the id of the sound effect
std::string SoundEffect::getID() {
	return id;
}

// returns the sound object
Mix_Chunk* SoundEffect::getSound() {
	return sound;
}
