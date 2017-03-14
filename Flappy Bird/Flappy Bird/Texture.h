#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//Texture wrapper class
class Texture {
public:
	// Constructor
	Texture();
	Texture(SDL_Renderer* gRenderer, std::string ID, std::string path, int width, int height, int x, int y);
	
	// Destructor
	~Texture();

	// Loads image at specified path - if you want to load entire image set width, height, x and y to 0
	bool loadFromFile(SDL_Renderer* gRenderer, std::string path, int width, int height, int x, int y);
	bool loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font *gFont, std::string textureText, int textColor[3]);

	//Deallocates texture
	void free();
	
	//Renders texture at given point 
	void render(SDL_Renderer* gRenderer, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// set the texture id
	void setID(std::string ID);

	//Gets image dimensions
	int getWidth();
	int getHeight();
	std::string getID();
	
	// returns the texture object
	SDL_Texture* getTexture();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Rect rect;
	std::string id;
	TTF_Font* font;

	//Image dimensions
	int mWidth;
	int mHeight;
};
