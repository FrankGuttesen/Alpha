#include "InputManager.h"
#include <SDL.h>
#include <chrono>
#include <thread>

// constructor
InputManager::InputManager()
{
	_isAnyKeyPressed = false;
	_isMousePressed = false;
}

// destructor
InputManager::~InputManager()
{
}

// checks if any key or mouse is pressed
void InputManager::pollInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			_isMousePressed = true;
			break;
		case SDL_MOUSEBUTTONUP:
			_isMousePressed = false;
			break;
		case SDL_QUIT:
			pressKey('quit'); // escape
			SDL_Quit();
			break;
		case SDL_KEYDOWN:
			if (!_isAnyKeyPressed) {
				pressKey(evnt.key.keysym.sym);
				_isAnyKeyPressed = true;
			}
			break;
		case SDL_KEYUP:
			releaseKey(evnt.key.keysym.sym);
			break;
		} // end switch evnt.type
	} // end while
}

// puts a key in to the map
void InputManager::pressKey(unsigned int keyID) {
	_keyMap[keyID] = true;
}

// removes a key from the map
void InputManager::releaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;
	_isAnyKeyPressed = false;
}

// checks if a key is in the key map
bool InputManager::isKeyPressed(unsigned int keyID) {
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}

// checks if any key is currently pressed/in the map
bool InputManager::isAnyKeyPressed() {
	return _isAnyKeyPressed;
}

// checks if a mouse button is pressed
bool InputManager::isMousePressed() {
	return _isMousePressed;
}

// set mouse pressed to false
void InputManager::releaseMouseButton() {
	_isMousePressed = false;
}