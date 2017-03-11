#include "Song.h"
#include "Errors.h"

Song::Song(std::string id, char fileName[]){
	setID(id);
	setSong(fileName);
}

Song::~Song(){
}

void Song::setID(std::string _id) {
	id = _id;
}

void Song::setSong(char fileName[]) {
	song = Mix_LoadMUS(fileName);
	if (song == NULL){
		fatalError("Failed to load music! SDL_mixer Error: %s\n");
	}
}

std::string Song::getID() {
	return id;
}
