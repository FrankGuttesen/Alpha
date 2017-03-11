#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string ID, int x, int y, bool s, Priority p)
{
	id = ID;
	posX = x;
	posY = y;
	solid = s;
	priority = p;
}

GameObject::~GameObject()
{
}

void GameObject::setPosX(int x) {
	posX = x;
}

void GameObject::setPosY(int y) {
	posY = y;
}

void GameObject::setSolid(bool s) {
	solid = s;
}

void GameObject::setID(std::string ID) {
	id = ID;
}

void GameObject::setPriority(Priority p) {
	priority = p;
}

int GameObject::getPosX() {
	return posX;
	
}

int GameObject::getPosY() {
	return posY;
}

bool GameObject::getSolid() {
	return solid;
}

std::string GameObject::getID() {
	return id;
}

Priority GameObject::getPriority() {
	return priority;
}


