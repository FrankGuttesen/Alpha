#pragma once
#include <vector>
#include "Texture.h"

// class that creates an animation from a vector of textures
class Animation
{
public:
	// constructor - takes a string id and vector of textures
	Animation(std::string ID, std::vector<Texture>sprites);

	// destructor
	~Animation();

	// plays a certain frame of the animation
	void playAnimation(SDL_Renderer *renderer, int x, int y, double angle);
	
	// returns animation id
	std::string getID();

private:
	// counter keeps check on which frame is to be processed
	int counter;
	
	// animation id
	std::string id;

	// contains the frames of the animation as textures
	std::vector<Texture>animation;
};


