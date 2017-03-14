#pragma once
#include <time.h>
#include <vector>
#include <memory>
#include <string>

#include "Window.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "FpsLimiter.h"
#include "GameObject.h"
#include "Texture.h"

// the various states the game can be in
enum GameStates
{
	MENU,
	PLAYING,
	GAME_OVER
};

class MainGame
{
public:
	// constructor
	MainGame();

	// destructor
	~MainGame();

	// initialise systems and load object/resources
	void init();
	void loadAudio();
	void loadSprites();
	void loadGameObjects();
	void loadFonts();

	// game functionality
	void run();
	void processInput();
	void update();
	void checkCollision();
	void render();
	void resetPlayer();
	void resetPipes();


private:
	// game variables
	bool passedPipe;
	bool passedPipe2;
	bool godMode;
	bool running;
	bool renderFPS;
	GameStates state;

	int score;
	int highScore;

	float gameSpeed;
	float gravity;
	float acceleration;
	float maxAcceleration;

	// Gameobjects kunnu eventuelt vera í world/lvl klassa ella einum object manager
	GameObject player;
	GameObject pipeTop;
	GameObject pipeBottom;
	GameObject pipeTop2;
	GameObject pipeBottom2;

	// Engine functionality
	InputManager inputManager;
	FpsLimiter limiter;
	Window window;
	SpriteManager spriteManager;
	AudioManager audioManager;

	// vector of objects that are to be rendered each iteration
	std::vector<GameObject>renderables;
};

