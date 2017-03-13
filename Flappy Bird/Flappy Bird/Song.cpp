#include "Song.h"
#include "Errors.h"

// constructor
Song::Song(std::string id, char fileName[]){
	setID(id);
	setSong(fileName);
}

// detructor
Song::~Song(){
	song = NULL;
}

// sets the song id
void Song::setID(std::string _id) {
	id = _id;
}

// sets the song object
void Song::setSong(char fileName[]) {
	song = Mix_LoadMUS(fileName);
	if (song == NULL){
		fatalError("Failed to load music! SDL_mixer Error: %s\n");
	}
}

// returns the song id
std::string Song::getID() {
	return id;
}

// returns the song object
Mix_Music* Song::getSong() {
	return song;
}