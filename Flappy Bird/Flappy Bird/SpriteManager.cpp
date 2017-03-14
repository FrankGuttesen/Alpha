#include "SpriteManager.h"
#include "Errors.h"

// constructors
SpriteManager::SpriteManager()
{
}

SpriteManager::SpriteManager(Window* window)
{
	// Create renderer for window
	Renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
	if (Renderer == NULL) {
		Error("Renderer could not be created! SDL Error: " + *SDL_GetError());
	}
	else {
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)){
			Error("SDL_image could not initialize! SDL_mage Error: " + *IMG_GetError());
		}
		//Initialize SDL_ttf
		if (TTF_Init() == -1) {
			Error("SDL_ttf could not initialize! SDL_ttf Error: " + *TTF_GetError());
		}
	}
}

// destructor
SpriteManager::~SpriteManager()
{
}

// deletes objects in vector and closes sdl subsystems
void SpriteManager::close() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->free();
	}
	for (int i = 0; i < sprites.size(); i++) {
		delete sprites[i];
	}
	for (int i = 0; i < fonts.size(); i++) {
		delete fonts[i];
	}

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
}

// creates a new texture and puts it in the vector
void SpriteManager::newSprite(std::string ID, std::string path, int width, int height, int x, int y) {
	Texture *newSprite = new Texture();
	newSprite->setID(ID);
	newSprite->loadFromFile(Renderer, path, width, height, x, y);
	sprites.push_back(newSprite);
}

// creates a new font texture
void SpriteManager::newFont(std::string ID, const char* fontPath, int size) {
	//Open the font
	TTF_Font* gFont = TTF_OpenFont(fontPath, size);
	if (gFont == NULL) {
		Error("Failed to load font! SDL_ttf Error: " + *TTF_GetError());
	}
	else {
		fonts.push_back(new Font(ID, gFont));
	}
}

// creates a new font texture
void SpriteManager::newFontTexture(std::string ID, std::string fontID, int size, std::string textureText, int textColor[3]) {
	Texture *newFont = new Texture();
	newFont->setID(ID);
	TTF_Font* gFont = NULL;

	for (int i = 0; i < fonts.size(); i++) {
		if (fonts[i]->getID() == fontID) {
			gFont = fonts[i]->getFont();
		}
	}

	if (!gFont == NULL) {
		if (!newFont->loadFromRenderedText(Renderer, gFont, textureText, textColor))
		{
			Error("Failed to render text texture!");
		}
		sprites.push_back(newFont);
	}
	else {
		Error("Did not find font");
	}
}

// updates the text in a specific font texture
void SpriteManager::updateFontTexture(std::string ID, std::string fontID, std::string textureText, int textColor[3]) {
	TTF_Font* gFont = NULL;
	for (int i = 0; i < fonts.size(); i++) {
		if (fonts[i]->getID() == fontID) {
			gFont = fonts[i]->getFont();
		}
	}
	if (!gFont == NULL) {
		for (int i = 0; i < sprites.size(); i++) {
			if (sprites[i]->getID() == ID) {
				sprites[i]->free();
				Texture *newFont = new Texture();
				newFont->setID(ID);
				if (!newFont->loadFromRenderedText(Renderer, gFont, textureText, textColor))
				{
					Error("Failed to update text texture!");
				}
				sprites[i] = newFont;
			}
		}
	}
	else {
		Error("Did not find font");
	}
}

// render a sprite to the screen
void SpriteManager::render(int x, int y, double angle, std::string id) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getID() == id) {
			sprites[i]->render(Renderer, x, y, angle);
		}
	}
}

// returns the height of a sprite
int SpriteManager::getSpriteHeight(std::string id) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getID() == id) {
			return sprites[i]->getHeight();
		}
	}
	return -1;
}

// returns the width of a sprite
int SpriteManager::getSpriteWidth(std::string id) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getID() == id) {
			return sprites[i]->getWidth();
		}
	}
	return -1;
}

// creates an animation from a vector of sprites
void SpriteManager::createAnimation(std::string id,  std::vector<std::string>SpriteIds) {
	std::vector<Texture>animation;
	for (int i = 0; i < SpriteIds.size(); i++) {
		animation.push_back(getSprite(SpriteIds[i]));
	}
	Animation anim(id, animation);
	animations.push_back(anim);

}

// renders a frame of a specific animation
void SpriteManager::renderAnimation(std::string ID, int x, int y, double angle) {
	for (int i = 0; i < animations.size(); i++) {
		if (animations[i].getID() == ID) {
			animations[i].playAnimation(Renderer, x, y, angle);
		}
	}
}

// returns a sprite as a texture object
Texture SpriteManager::getSprite(std::string id) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getID() == id) {
			return *sprites[i];
		}
	}
}

// sets the default draw color of the renderer
void SpriteManager::SetRenderDrawColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(Renderer, r, g, b, a);
}

// clears the render buffer
void SpriteManager::RenderClear() {
	SDL_RenderClear(Renderer);
}

// renders all objects in the render buffer
void SpriteManager::RenderPresent() {
	SDL_RenderPresent(Renderer);
}

