#pragma once
#include <SDL_image.h>
#include <vector>

#include "Window.h"
#include "Texture.h"

class SpriteManager
{
public:
	SpriteManager();
	SpriteManager(Window *window);
	~SpriteManager();

	void newSprite(std::string ID, std::string path, int width, int height, int x, int y);
	void render(int x, int y, std::string id);
	int getSpriteHeight(std::string id);
	int getSpriteWidth(std::string id);


	void SetRenderDrawColor(int r, int g, int b, int a);
	void RenderClear();
	void RenderPresent();

private:
	std::vector<Texture*>sprites;
	SDL_Renderer* Renderer;
};

