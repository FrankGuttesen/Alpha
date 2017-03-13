#pragma once
#include <SDL.h>
#include <string>

// flags for window settings
enum WindowFlags{ INVISIBLE = 0x8, FULLSCREEN = 0x1, BORDERLESS = 0x10, SHOWN = 0x4 };

class Window
{
public:
	// constructor
	Window();

	// destructor
	~Window();
	void close();

	// creates a new window
	int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

	// returns window dimensions
	int getScreenWidth();
	int getScreenHeight();

	// returns an SDL_Window*
	SDL_Window* getWindow();

private:
	bool vsync;
	// variables
	SDL_Window* _sdlWindow;
	SDL_Surface* _ScreenSurface;
	int _screenWidth;
	int _screenHeight;
};
