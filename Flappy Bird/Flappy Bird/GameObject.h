#pragma once
#include <string>
#include "Texture.h"

enum Priority {
	FOREGROUND,
	PLAYER,
	MIDDLEGROUND,
	BACKGROUND,
	DO_NOT_RENDER
};

class GameObject
{
public:
	GameObject();
	GameObject(std::string ID, int x, int y, bool s, Priority p);
	~GameObject();

	void setPosX(int x);
	void setPosY(int y);
	void setSolid(bool s);
	void setID(std::string ID);
	void setPriority(Priority p);
	
	int getPosX();
	int getPosY();
	bool getSolid();
	std::string getID();
	Priority getPriority();

private:
	int posX;
	int posY;
	bool solid;
	std::string id;
	Priority priority;
};

