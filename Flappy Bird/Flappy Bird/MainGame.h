#pragma once
#include <time.h>
#include <vector>
#include <memory>

#include "Window.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "FpsLimiter.h"
#include "GameObject.h"
#include "Texture.h"


enum GameStates
{
	MENU,
	PLAYING,
	GAME_OVER
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void init();

	bool loadAudio();
	void loadSprites();
	void loadGameObjects();

	void run();
	void processInput();
	void update();
	void checkCollision();
	void render();
	void resetPlayer();
	void resetPipes();


private:
	bool passedPipe;
	bool passedPipe2;
	bool godMode;
	int score;
	float gameSpeed;
	float gravity;
	float acceleration;
	float maxAcceleration;

	// game variables
	bool running;
	GameStates state;

	// Engine functionality
	Window window;	// gera ein enum wrappara til Window FLAGS
	SpriteManager spriteManager;
	InputManager inputManager;
	AudioManager audioManager;
	FpsLimiter limiter;
	
	// Gameobjects høvdu eventuelt kunna veri í world/lvl klassa
	GameObject player;
	GameObject pipeTop;
	GameObject pipeBottom;
	GameObject pipeTop2;
	GameObject pipeBottom2;

	// vector of objects that are to be rendered each iteration
	std::vector<GameObject>renderables;

};

