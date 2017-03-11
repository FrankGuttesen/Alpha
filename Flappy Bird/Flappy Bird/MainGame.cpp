#include "MainGame.h"
#include "Errors.h"
#include <iostream>

// constructor
MainGame::MainGame()
{
	state = MENU;
	running = true;
	gravity = -0.3;
	acceleration = 0;
	gameSpeed = 3.3;
	maxAcceleration = 5;
	score = 0;
	passedPipe = false;
	passedPipe2 = false;
	godMode = false;

	// create a window
	window.create("Flappy Bird", 400, 500, SHOWN);
	spriteManager = SpriteManager(&window);
}

// destructor
MainGame::~MainGame() {
	window.~Window();
	audioManager.~AudioManager();
	spriteManager.~SpriteManager();

	//Destroy window	
	window.~Window();
}

// initialise systems/variables
void MainGame::init() {
	bool success = true;

	loadGameObjects();

	if (!loadAudio()) {
		success = false;
		printf("Failed to load audio!");
	}

	loadSprites();

	resetPlayer();
	resetPipes();
}

void MainGame::loadGameObjects() {
	player = GameObject("player", window.getScreenWidth() / 8, window.getScreenHeight() / 2, true, PLAYER);

	// seed random number for the height of the pipes
	srand(time(NULL));
	int newHeight = rand() % 200 + 150;
	pipeTop = GameObject("pipeTop", window.getScreenWidth(), -newHeight, true, FOREGROUND);
	pipeBottom = GameObject("pipeBottom", window.getScreenWidth(), -newHeight + 500, true, FOREGROUND);

	newHeight = rand() % 200 + 150;
	pipeTop2 = GameObject("pipeTop2", pipeTop.getPosX() + 300, -newHeight, true, FOREGROUND);
	pipeBottom2 = GameObject("pipeBottom2", pipeTop.getPosX() + 300, -newHeight + 500, true, FOREGROUND);

	passedPipe = false;
	passedPipe2 = false;
}

// loads audio into the audio manager
bool MainGame::loadAudio() {
	bool success = true;


	// load soundEffects
	if (!audioManager.loadSoundEffect("death", "Audio/select1.wav")) { success = false; }
	if (!audioManager.loadSoundEffect("next", "Audio/select3b.wav")) { success = false; }
	if (!audioManager.loadSoundEffect("coin", "Audio/smw_coin.wav")) { success = false; }

	// load Music
	if (!audioManager.loadSong("Kids_Music_3", "Audio/Kids_Music_3.wav")) { success = false; }

	audioManager.setSoundFXVolume(1, 128);
	audioManager.setMusicVolume(20);
	audioManager.playSong("Kids_Music_3");

	return success;
}

// load Sprites
void MainGame::loadSprites() {
	spriteManager.newSprite("background", "Sprites/sheet.png", 275, 111, 0, 0);
	spriteManager.newSprite("ground", "Sprites/sheet.png", 225, 110, 275, 0);
	spriteManager.newSprite("pipeTop", "Sprites/sheet.png", 54, 400, 552, 0);
	spriteManager.newSprite("pipeBottom", "Sprites/sheet.png", 52, 400, 502, 0);
	spriteManager.newSprite("pipeTop2", "Sprites/sheet.png", 54, 400, 552, 0);
	spriteManager.newSprite("pipeBottom2", "Sprites/sheet.png", 52, 400, 502, 0);

	spriteManager.newSprite("player", "Sprites/sheet.png", 34, 24, 311, 230);

	spriteManager.newSprite("flappyBird", "Sprites/sheet.png", 192, 44, 118, 228);
	spriteManager.newSprite("getReady", "Sprites/sheet.png", 174, 44, 118, 310);
	spriteManager.newSprite("menu", "Sprites/sheet.png", 118, 122, 0, 228);

	spriteManager.newSprite("gameOver", "Sprites/sheet.png", 192, 38, 118, 272);
	spriteManager.newSprite("scoreScreen", "Sprites/sheet.png", 227, 115, 275, 111);
	spriteManager.newSprite("coinWhite", "Sprites/sheet.png", 44, 45, 348, 228);
	spriteManager.newSprite("coinSilver", "Sprites/sheet.png", 44, 45, 397, 228);
	spriteManager.newSprite("coinBronze", "Sprites/sheet.png", 44, 45, 397, 274);
	spriteManager.newSprite("coinGold", "Sprites/sheet.png", 44, 45, 348, 274);

}

// main game loop
void MainGame::run() {
	init();

	limiter.setMaxFPS(100);
	while (running) {
		limiter.begin();
		update();
		limiter.end();
		render();
	}
}

// gets user input and acts upon it
void MainGame::processInput() {
	inputManager.pollInput();

	if (inputManager.isMousePressed() || inputManager.isKeyPressed(0x20)) { // SPACE
		if (state == PLAYING) {
			acceleration += 5;
		}
		if (state == MENU) {
			acceleration = maxAcceleration;
			inputManager.releaseKey(0x20);
			inputManager.releaseMouseButton();
			audioManager.playSound("coin");
			state = PLAYING;
		}
		if (state == GAME_OVER) {
			score = 0;
			resetPlayer();
			resetPipes();
			inputManager.releaseKey(0x20);
			inputManager.releaseMouseButton();
			audioManager.playSound("next");
			state = MENU;
		}
	}

	if (inputManager.isKeyPressed(0x1B)) { // ESCAPE
		running = false;
	}
	if (inputManager.isKeyPressed('quit')) { // window exit
		running = false;
	}

	// keys for audio
	if (inputManager.isKeyPressed('5')) {
		audioManager.playSong("Kids_Music_3");
		inputManager.releaseKey('5');
	}
	if (inputManager.isKeyPressed('6')) {
		audioManager.playSong("stop");
		inputManager.releaseKey('6');
	}
	if (inputManager.isKeyPressed('+')) {
		audioManager.increaseMusicVolume();
		inputManager.releaseKey('+');
	}
	if (inputManager.isKeyPressed('-')) {
		audioManager.lowerMusicVolume();
		inputManager.releaseKey('-');
	}
	if (inputManager.isKeyPressed('<')) {
		audioManager.increaseSoundFXVolume();
		inputManager.releaseKey('<');
	}
	if (inputManager.isKeyPressed('z')) {
		audioManager.lowerSoundFXVolume();
		inputManager.releaseKey('z');
	}
}

void MainGame::update() {
	// get user input
	processInput();

	if (state == PLAYING) {
		// clear the vector of objects to render
		renderables.clear();

		// set acceleration for player
		acceleration += gravity;
		if (acceleration > maxAcceleration) {
			acceleration = maxAcceleration;
		}

		// set player position
		player.setPosY(player.getPosY() - acceleration);


		// move pipes to the left
		pipeTop.setPosX(pipeTop.getPosX() - gameSpeed);
		pipeBottom.setPosX(pipeBottom.getPosX() - gameSpeed);
		pipeTop2.setPosX(pipeTop2.getPosX() - gameSpeed);
		pipeBottom2.setPosX(pipeBottom2.getPosX() - gameSpeed);


		// set score
		int width = spriteManager.getSpriteWidth("pipeTop");
		if (player.getPosX() >= pipeTop.getPosX() + width && passedPipe == false) {
			audioManager.playSound("coin");
			score++;
			passedPipe = true;
		}
		if (player.getPosX() >= pipeTop2.getPosX() + width && passedPipe2 == false) {
			audioManager.playSound("coin");
			score++;
			passedPipe2 = true;
		}


		// reset pipes
		// seed random number for the height of the pipes
		srand(time(NULL));
		int newHeight = rand() % 200 + 150;

		if (pipeBottom.getPosX() <= -60) {
			pipeTop.setPosX(pipeTop2.getPosX() + 300);
			pipeTop.setPosY(-newHeight);
			pipeBottom.setPosX(pipeTop2.getPosX() + 300);
			pipeBottom.setPosY(-newHeight + 500);
			passedPipe = false;
		}

		newHeight = rand() % 200 + 150;
		if (pipeBottom2.getPosX() <= -60) {
			pipeTop2.setPosX(pipeTop.getPosX() + 300);
			pipeTop2.setPosY(-newHeight);
			pipeBottom2.setPosX(pipeTop.getPosX() + 300);
			pipeBottom2.setPosY(-newHeight + 500);
			passedPipe2 = false;
		}


		// check for collision
		checkCollision();

		// put game objects in to vector of items to render
		renderables.push_back(player);

		// limit renderable objects by their vicinity to the viewport
		if (pipeTop.getPosX() > -1000 && pipeTop.getPosX() < window.getScreenWidth() + 1000) {
			if (pipeTop.getPosY() > -1000 && pipeTop.getPosY() < window.getScreenHeight() + 1000) {
				renderables.push_back(pipeTop);
			}
		}
		if (pipeBottom.getPosX() > -1000 && pipeBottom.getPosX() < window.getScreenWidth() + 1000) {
			if (pipeBottom.getPosY() > -1000 && pipeBottom.getPosY() < window.getScreenHeight() + 1000) {
				renderables.push_back(pipeBottom);
			}
		}
		if (pipeTop2.getPosX() > -1000 && pipeTop.getPosX() < window.getScreenWidth() + 1000) {
			if (pipeTop.getPosY() > -1000 && pipeTop.getPosY() < window.getScreenHeight() + 1000) {
				renderables.push_back(pipeTop2);
			}
		}
		if (pipeBottom2.getPosX() > -1000 && pipeBottom2.getPosX() < window.getScreenWidth() + 1000) {
			if (pipeBottom2.getPosY() > -1000 && pipeBottom2.getPosY() < window.getScreenHeight() + 1000) {
				renderables.push_back(pipeBottom2);
			}
		}
	}
}

// check for collisions
void MainGame::checkCollision() {
	int height, height2, width, width2;

	// if player hits bottom of screen
	height = spriteManager.getSpriteHeight("player");
	height2 = spriteManager.getSpriteHeight("ground");
	if (player.getPosY() + height > window.getScreenHeight() - height2) {
		std::cout << "Collided Bottom!" << std::endl;
		if (!godMode) {
			audioManager.playSound("death");
			state = GAME_OVER;
		}
	}

	// if player hits top of screen
	if (player.getPosY() < 0) {
		std::cout << "Collided Top!" << std::endl;
		if (!godMode) {
			audioManager.playSound("death");
			state = GAME_OVER;
		}
	}

	// top pipe collision detection
	height = spriteManager.getSpriteHeight("player");
	width = spriteManager.getSpriteWidth("player");

	height2 = spriteManager.getSpriteHeight("pipeTop");
	width2 = spriteManager.getSpriteWidth("pipeTop");

	if (player.getPosX() + width / 2 >= pipeTop.getPosX() && player.getPosX() <= pipeTop.getPosX() + width2) {
		if (player.getPosY() <= (pipeTop.getPosY() + height2)) {
			std::cout << "Collided With Top Pipe!" << std::endl;
			if (!godMode) {
				audioManager.playSound("death");
				state = GAME_OVER;
			}
		}
	}

	// bottom pipe collision detection
	height = spriteManager.getSpriteHeight("player");
	width = spriteManager.getSpriteWidth("player");
	height2 = spriteManager.getSpriteHeight("pipeBottom");
	width2 = spriteManager.getSpriteWidth("pipeBottom");

	if (player.getPosX() + width / 2 >= pipeBottom.getPosX() && player.getPosX() <= pipeBottom.getPosX() + width2) {
		if (player.getPosY() + height >= pipeBottom.getPosY()) {
			std::cout << "Collided With pipeBottom!" << std::endl;
			if (!godMode) {
				audioManager.playSound("death");
				state = GAME_OVER;
			}
		}
	}

	// top pipe2 collision detection
	height = spriteManager.getSpriteHeight("player");
	width = spriteManager.getSpriteWidth("player");
	height2 = spriteManager.getSpriteHeight("pipeTop2");
	width2 = spriteManager.getSpriteWidth("pipeTop2");

	if (player.getPosX() + width / 2 >= pipeTop2.getPosX() && player.getPosX() <= pipeTop2.getPosX() + width2) {
		if (player.getPosY() <= (pipeTop2.getPosY() + height2)) {
			std::cout << "Collided With pipeTop2!" << std::endl;
			if (!godMode) {
				audioManager.playSound("death");
				state = GAME_OVER;
			}
		}
	}

	// bottom pipe collision detection
	height = spriteManager.getSpriteHeight("player");
	width = spriteManager.getSpriteWidth("player");
	height2 = spriteManager.getSpriteHeight("pipeBottom2");
	width2 = spriteManager.getSpriteWidth("pipeBottom2");

	if (player.getPosX() + width / 2 >= pipeBottom2.getPosX() && player.getPosX() <= pipeBottom2.getPosX() + width2) {
		if (player.getPosY() + height >= pipeBottom2.getPosY()) {
			std::cout << "Collided With pipeBottom2!" << std::endl;
			if (!godMode) {
				audioManager.playSound("death");
				state = GAME_OVER;
			}
		}
	}
}

// renders items to the window
void MainGame::render() {
	int height, width, counter;
	//Clear screen
	spriteManager.SetRenderDrawColor(111, 170, 230, 255);
	spriteManager.RenderClear();

	//Render background at x,y
	counter = 0;
	height = spriteManager.getSpriteHeight("background");
	width = spriteManager.getSpriteWidth("background");
	while (counter < window.getScreenWidth()) {
		spriteManager.render(counter, window.getScreenHeight() - (height * 2), "background");
		counter += width;
	}

	// render ground
	counter = 0;
	height = spriteManager.getSpriteHeight("ground");
	width = spriteManager.getSpriteWidth("ground");
	while (counter < window.getScreenWidth()) {
		spriteManager.render(counter, window.getScreenHeight() - height, "ground");
		counter += width;
	}



	if (state == PLAYING) {
		if (renderables.size() != 0) {
			int priority = BACKGROUND;
			while (priority >= 0) {
				for (int i = 0; i < renderables.size(); i++) {
					if (renderables[i].getPriority() == priority) {
						spriteManager.render(renderables[i].getPosX(), renderables[i].getPosY(), renderables[i].getID());
					}
				}
				priority--;
			}
		}

		//std::cout << "SCORE: " << score << std::endl;

	}

	if (state == MENU) {
		width = spriteManager.getSpriteWidth("flappyBird");
		spriteManager.render((window.getScreenWidth() / 2) - (width / 2), window.getScreenHeight() / 8, "flappyBird");

		width = spriteManager.getSpriteWidth("getReady");
		spriteManager.render((window.getScreenWidth() / 2) - (width / 2), window.getScreenHeight() / 3, "getReady");

		width = spriteManager.getSpriteWidth("menu");
		spriteManager.render((window.getScreenWidth() / 2) - (width / 2), window.getScreenHeight() / 2, "menu");

	}

	if (state == GAME_OVER) {
		width = spriteManager.getSpriteWidth("gameOver");
		spriteManager.render((window.getScreenWidth() / 2) - (width / 2), window.getScreenHeight() / 5, "gameOver");

		height = spriteManager.getSpriteHeight("scoreScreen");
		width = spriteManager.getSpriteWidth("scoreScreen");
		spriteManager.render((window.getScreenWidth() / 2) - (width / 2), (window.getScreenHeight() / 3) + height / 2, "scoreScreen");

		height = 267;
		width = 115;
		if (score < 5) {
			spriteManager.render(width, height, "coinWhite");
		}
		if (score > 4 && score < 10) {
			spriteManager.render(width, height, "coinBronze");
		}
		if (score > 9 && score < 15) {
			spriteManager.render(width, height, "coinSilver");
		}
		if (score > 14 && score < 20) {
			spriteManager.render(width, height, "coinGold");
		}
	}

	//Update screen
	spriteManager.RenderPresent();
}

// reset player position
void MainGame::resetPlayer() {
	player = GameObject("player", window.getScreenWidth() / 8, window.getScreenHeight() / 2, true, PLAYER);
}

// reset pipes position
void MainGame::resetPipes() {
	// seed random number for the height of the pipes
	srand(time(NULL));
	int newHeight = rand() % 200 + 150;
	pipeTop = GameObject("pipeTop", window.getScreenWidth(), -newHeight, true, FOREGROUND);
	pipeBottom = GameObject("pipeBottom", window.getScreenWidth(), -newHeight + 500, true, FOREGROUND);
	passedPipe = false;

	newHeight = rand() % 200 + 150;
	pipeTop2 = GameObject("pipeTop2", pipeTop.getPosX() + 300, -newHeight, true, FOREGROUND);
	pipeBottom2 = GameObject("pipeBottom2", pipeTop.getPosX() + 300, -newHeight + 500, true, FOREGROUND);
	passedPipe2 = false;
}
