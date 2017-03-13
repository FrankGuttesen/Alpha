#pragma once
#include <string>
#include "Texture.h"

// enum that sets the objects render priority
enum Priority {
	FOREGROUND,
	PLAYER,
	MIDDLEGROUND,
	BACKGROUND,
	DO_NOT_RENDER
};

// defines a gameobject that can be rendered or collided with
// can be used as a base class for more specific objects such as player
class GameObject
{
public:
	// constructors
	GameObject();
	GameObject(std::string ID, int x, int y, double angle, bool s, Priority p);

	// destructor
	~GameObject();

	// set object variables
	void setPosX(int x);
	void setPosY(int y);
	void setAngle(double a);
	void increaseAngle(double a);
	void decreaseAngle(double a);
	void setSolid(bool s);
	void setID(std::string ID);
	void setPriority(Priority p);
	
	// retrieve object variables
	int getPosX();
	int getPosY();
	double getAngle();
	bool getSolid();
	std::string getID();
	Priority getPriority();

private:
	// variables
	int posX;
	int posY;
	double angle;
	bool solid;
	std::string id;
	Priority priority;
};

