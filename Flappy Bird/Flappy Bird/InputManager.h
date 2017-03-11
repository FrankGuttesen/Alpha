#pragma once
#include <unordered_map>
class InputManager
{
public:
	InputManager();
	~InputManager();

	void pollInput();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
	bool isAnyKeyPressed();
	bool isMousePressed();
	void releaseMouseButton();

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	bool _isAnyKeyPressed;
	bool _isMousePressed;
};



