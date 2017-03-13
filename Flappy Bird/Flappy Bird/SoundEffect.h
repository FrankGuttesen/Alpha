#pragma once
#include <SDL_mixer.h>
#include <string>

// creates a sound effect for the audio manager
class SoundEffect
{
public:
	// constructor
	SoundEffect(std::string id, char fileName[]);

	// destructor
	~SoundEffect();

	// set the sound id
	void setID(std::string _id);

	// set the sound object from filepath
	void setSound(char fileName[]);

	// returns the sounds' id
	std::string getID();

	// returns the sound object
	Mix_Chunk* getSound();

private:
	// variables
	std::string id;
	Mix_Chunk *sound;
};

