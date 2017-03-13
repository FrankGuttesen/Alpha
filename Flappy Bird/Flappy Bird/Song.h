#pragma once
#include <SDL_mixer.h>
#include <string>

// creates a song object for the audio manager
class Song{
public:
	// constructor
	Song(std::string id, char fileName[]);

	// destructor
	~Song();

	// set the song id
	void setID(std::string _id);

	// load the song from filepath
	void setSong(char fileName[]);

	// returns the song id
	std::string getID();

	// returns the song
	Mix_Music* getSong();
	
private:
	// variables
	std::string id;
	Mix_Music *song;
};

