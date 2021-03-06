#pragma once
class FpsLimiter {
public:
	// constructor
	FpsLimiter();

	// Initializes the FPS limiter. For now, this is analogous to setMaxFPS
	void init(float maxFPS);

	// Sets the desired max FPS
	void setMaxFPS(float maxFPS);

	// start the limiter
	void begin();

	// end() will return the current FPS as a float
	float end();

	// returns the current fps
	double getFPS();

private:
	// Calculates the current FPS
	void calculateFPS();

	// Variables
	float _fps;
	float _maxFPS;
	float _frameTime;
	unsigned int _startTicks;
};
