#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "Window.h"
#include "Texture.h"
#include "Animation.h"
#include "Font.h"

// allows for sprite, animation & font creation, stores them in vectors
// also creates the graphics renderer used to render to the window
class SpriteManager
{
public:
	// constructors
	SpriteManager();
	SpriteManager(Window *window);

	// destructor
	~SpriteManager();
	void close();

	// create new sprites/animation/fonts
	void newSprite(std::string ID, std::string path, int width, int height, int x, int y);
	void newFont(std::string ID, const char* fontPath, int size);
	void newFontTexture(std::string ID, std::string fontID, int size, std::string textureText, int textColor[3]);
	void createAnimation(std::string id, std::vector<std::string>SpriteIds);
	
	// updates an old font texture with new text
	void updateFontTexture(std::string ID, std::string textureText, std::string fontID, int textColor[3]);

	// render sprite/animation to the screen
	void render(int x, int y, double angle, std::string id);
	void renderAnimation(std::string id, int x, int y, double angle);

	// get functions
	Texture getSprite(std::string id);
	int getSpriteHeight(std::string id);
	int getSpriteWidth(std::string id);

	// renderer functions
	void SetRenderDrawColor(int r, int g, int b, int a);
	void RenderClear();
	void RenderPresent();

private:
	// variables
	SDL_Renderer* Renderer;
	std::vector<Texture*>sprites;
	std::vector<Animation>animations;
	std::vector<Font*>fonts;
};
