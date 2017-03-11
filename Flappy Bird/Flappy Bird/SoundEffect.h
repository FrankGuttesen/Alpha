#pragma once
#include <SDL_mixer.h>
#include <string>

class SoundEffect
{
public:
	SoundEffect(std::string id, char fileName[]);
	~SoundEffect();

	void setID(std::string _id);
	void setSound(char fileName[]);
	std::string getID();

	Mix_Chunk *sound;

private:
	std::string id;
};

