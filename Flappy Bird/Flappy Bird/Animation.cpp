#include "Animation.h"

Animation::Animation(std::string ID, std::vector<Texture>sprites) : counter(0)
{
	id = ID;
	for (int i = 0; i < sprites.size(); i++) {
		animation.push_back(sprites[i]);
	}
}


Animation::~Animation()
{
	for (int i = 0; i < animation.size(); i++) {
		animation[i].free();
	}
}


void Animation::playAnimation(SDL_Renderer *renderer, int x, int y) {
	if (counter == animation.size()) {
		counter = 0;
	}
	animation[counter].render(renderer, x, y);
	counter++;
}

std::string Animation::getID() {
	return id;
}