#pragma once
#include <SDL_mixer.h>
#include <string>

class Song{
public:
	Song(std::string id, char fileName[]);
	~Song();

	void setID(std::string _id);
	void setSong(char fileName[]);

	std::string getID();

	Mix_Music *song;

private:
	std::string id;
};

