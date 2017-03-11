#pragma once
#include <vector>
#include "Texture.h"

class Animation
{
public:
	Animation(std::string ID, std::vector<Texture>sprites);
	~Animation();

	void playAnimation(SDL_Renderer *renderer, int x, int y);
	std::string getID();


private:
	int counter;
	std::string id;
	std::vector<Texture>animation;
};


