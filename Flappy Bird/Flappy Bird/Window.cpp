#include "Window.h"
#include "Errors.h"

// constructor
Window::Window()
{
	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}
}

// destructor
Window::~Window(){
	close();
}

// destroys window and closes sdl
void Window::close() {
	SDL_DestroyWindow(_sdlWindow);
	SDL_Quit();
}

// creates a new window
int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags){
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & INVISIBLE){
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN){
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS){
		flags |= SDL_WINDOW_BORDERLESS;
	}


	// Open an SDL Window
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if (_sdlWindow == nullptr){
		fatalError("SDL Window could not be created!");
	}

	// Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr){
		fatalError("SDL_GL context could not be created");
	}

	// Set VSYNC (1 = VSYNC on, 0 = VSYNC off)
	SDL_GL_SetSwapInterval(1);

	
	return 0;
}


// returns window width
int Window::getScreenWidth() { 
	return _screenWidth; 
}

// returns window height
int Window::getScreenHeight() {
	return _screenHeight; 
}

// returns the window as an SDL_Window*
SDL_Window* Window::getWindow() { 
	return _sdlWindow;
}