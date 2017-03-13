#include "Errors.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// prints error message and exits the game
void fatalError(std::string errorString){
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;

	// close sdl subsystems
	SDL_Quit();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();

	// quit program with error
	exit(1);
}

// prints error message
void Error(std::string errorString) {
	std::cout << errorString << std::endl;
}