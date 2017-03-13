#include "Animation.h"

// constructor - takes a string id and vector of textures
Animation::Animation(std::string ID, std::vector<Texture>sprites) : counter(0)
{
	id = ID;
	for (int i = 0; i < sprites.size(); i++) {
		animation.push_back(sprites[i]);
	}
}

// destructor - calls each texture objects delete function (free())
Animation::~Animation()
{
	for (int i = 0; i < animation.size(); i++) {
		animation[i].free();
	}
}

// plays a certain frame of the animation
void Animation::playAnimation(SDL_Renderer *renderer, int x, int y, double angle) {
	if (counter == animation.size()) {
		counter = 0;
	}
	animation[counter].render(renderer, x, y, angle);
	counter++;
}

// returns the animation's id
std::string Animation::getID() {
	return id;
}