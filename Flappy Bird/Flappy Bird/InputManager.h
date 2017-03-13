#pragma once
#include <unordered_map>

// stores input in a map (removes input lag from standard way of input)
class InputManager
{
public:
	// constructor
	InputManager();

	// destructor
	~InputManager();

	// check for input
	void pollInput();

	// press/release inputted key/mouse press
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	void releaseMouseButton();

	// check if certain key or mouse is pressed
	bool isKeyPressed(unsigned int keyID);
	bool isAnyKeyPressed();
	bool isMousePressed();

private:
	// variables
	bool _isAnyKeyPressed;
	bool _isMousePressed;

	// map of pressed keys/mouse
	std::unordered_map<unsigned int, bool> _keyMap;
};



