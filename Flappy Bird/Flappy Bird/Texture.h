#pragma once
#include <SDL_image.h>
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

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(SDL_Renderer* gRenderer, int x, int y);

	void setID(std::string ID);

	//Gets image dimensions
	int getWidth();
	int getHeight();
	std::string getID();
	
	SDL_Texture* getTexture();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Rect rect;

	std::string id;

	//Image dimensions
	int mWidth;
	int mHeight;
};
