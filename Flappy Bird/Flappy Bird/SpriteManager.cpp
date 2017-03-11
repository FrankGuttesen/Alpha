#include "SpriteManager.h"
#include <iostream>

// constructors
SpriteManager::SpriteManager() {
}

SpriteManager::SpriteManager(Window* window)
{
	// Create renderer for window
	Renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
	if (Renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else {
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
		}
	}

}

// destructor
SpriteManager::~SpriteManager()
{
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->free();
	}
	for (int i = 0; i < sprites.size(); i++) {
		delete sprites[i];
	}
	IMG_Quit();
}

// creates a new texture and puts it in the vector
void SpriteManager::newSprite(std::string ID, std::string path, int width, int height, int x, int y) {
	Texture *newSprite = new Texture();
	newSprite->setID(ID);
	newSprite->loadFromFile(Renderer, path, width, height, x, y);
	sprites.push_back(newSprite);
}

// render a sprite to the screen
void SpriteManager::render(int x, int y, std::string id) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getID() == id) {
			sprites[i]->render(Renderer, x, y);
		}
	}
}

int SpriteManager::getSpriteHeight(std::string id) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getID() == id) {
			return sprites[i]->getHeight();
		}
	}
	return -1;
}

int SpriteManager::getSpriteWidth(std::string id) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getID() == id) {
			return sprites[i]->getWidth();
		}
	}
	return -1;
}

void SpriteManager::SetRenderDrawColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(Renderer, r, g, b, a);
}

void SpriteManager::RenderClear() {
	SDL_RenderClear(Renderer);
}

void SpriteManager::RenderPresent() {
	SDL_RenderPresent(Renderer);
}

