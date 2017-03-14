#pragma once
#include <SDL_ttf.h>
#include <string>
class Font
{
public:
	Font(std::string ID, TTF_Font* Font);
	~Font();

	std::string getID();
	TTF_Font* getFont();

private:
	std::string id;
	TTF_Font *font;
};

