#include "Texture.h"
#include "Errors.h"

// empty constructor
Texture::Texture() {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	id = "";
}

// constructor
Texture::Texture(SDL_Renderer* gRenderer, std::string ID, std::string path, int width, int height, int x, int y) {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	id = ID;
	loadFromFile(gRenderer, path, width, height, x, y);
}

// destructor
Texture::~Texture() {
	// Deallocate
	free();
}

// deallocates texture variable
void Texture::free() {
	//Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		rect.h = 0;
		rect.w = 0;
		rect.x = 0;
		rect.y = 0;
		mWidth = 0;
		mHeight = 0;
	}
}

// loads an image from a file, saves it as a texture and returns true if successfull
bool Texture::loadFromFile(SDL_Renderer* gRenderer, std::string path, int width, int height, int x, int y){
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}else{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)	{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}else{
			mWidth = width;
			mHeight = height;
			rect.h = height;
			rect.w = width;
			rect.x = x;
			rect.y = y;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	// return success
	mTexture = newTexture;
	return mTexture != NULL;
}

// load a text with a given font as a texture
bool Texture::loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font *gFont, std::string textureText, int textColor[3]) {
	//Get rid of preexisting texture 
	free(); 

	SDL_Color color = { textColor[0], textColor[1], textColor[2]};
	//Render text surface 
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), color); 
	if( textSurface == NULL ) { 
		Error("Unable to render text surface! SDL_ttf Error: " + *TTF_GetError());
	} else { 
		//Create texture from surface pixels 
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface ); 
		if( mTexture == NULL ) {
			Error("Unable to create texture from rendered text! SDL Error: " + *SDL_GetError()); 
		} else {
			//Get image dimensions 
			mWidth = textSurface->w; 
			mHeight = textSurface->h; 
		} 
		//Get rid of old surface 
		SDL_FreeSurface( textSurface ); 
	} 
	//Return success 
	return mTexture != NULL;
}

// renders the texture to the screen
void Texture::render(SDL_Renderer* gRenderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	
	//Set clip rendering dimensions
	if (rect.w != 0) {
		renderQuad.w = rect.w;
	}if (rect.h != 0) {
		renderQuad.h = rect.h;
	}

	if (rect.w == 0 && rect.h == 0) {
		SDL_RenderCopyEx(gRenderer, mTexture, NULL, &renderQuad, angle, center, flip);
	}
	else {
		SDL_RenderCopyEx(gRenderer, mTexture, &rect, &renderQuad, angle, center, flip);
	}
}

// set the id of the texutre
void Texture::setID(std::string ID) {
	id = ID;
}

// returns the width of the texture
int Texture::getWidth() {
	return mWidth;
}

// returns the height of the texture
int Texture::getHeight() {
	return mHeight;
}

// returns the textures' id
std::string Texture::getID() {
	return id;
}

// returns the texture as a SDL_Texture* object
SDL_Texture* Texture::getTexture() {
	return mTexture;
}
