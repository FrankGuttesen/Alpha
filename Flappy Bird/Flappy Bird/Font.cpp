#include "Font.h"

Font::Font(std::string ID, TTF_Font* Font) {
	id = ID;
	font = Font;
}
Font::~Font() {
	font = NULL;
}

std::string Font::getID() { 
	return id; 
}

TTF_Font* Font::getFont() {
	return font; 
}