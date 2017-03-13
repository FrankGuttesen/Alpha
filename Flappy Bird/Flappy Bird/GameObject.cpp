#include "GameObject.h"

// empty constructor
GameObject::GameObject()
{
}

// constructor that sets variables
GameObject::GameObject(std::string ID, int x, int y, double Angle, bool s, Priority p)
{
	id = ID;
	posX = x;
	posY = y;
	angle = Angle;
	solid = s;
	priority = p;
}

// destructor
GameObject::~GameObject()
{
}

// sets the objects X position
void GameObject::setPosX(int x) {
	posX = x;
}

// sets the objects Y position
void GameObject::setPosY(int y) {
	posY = y;
}

// sets the angle the object is to be rendered at
void GameObject::setAngle(double a) {
	angle = a;
}

// increases the angle of which the object is to be rendered (clockwise)
void GameObject::increaseAngle(double a) {
	angle += a;
}

// decreases the angle of which the object is to be rendered (counter clockwise)
void GameObject::decreaseAngle(double a) {
	angle -= a;
}

// set the solidity of the object (determines wether object is collidable)
void GameObject::setSolid(bool s) {
	solid = s;
}

// sets the id of the object
void GameObject::setID(std::string ID) {
	id = ID;
}

// sets the render priority of the object
void GameObject::setPriority(Priority p) {
	priority = p;
}

// returns the X position of the object
int GameObject::getPosX() {
	return posX;
	
}

// returns the Y position of the object
int GameObject::getPosY() {
	return posY;
}

// returns the render angle of the object
double GameObject::getAngle() {
	return angle;
}

// get the solidity of the object (determines wether object is collidable)
bool GameObject::getSolid() {
	return solid;
}

// returns the id of the object
std::string GameObject::getID() {
	return id;
}

// returns the render priority of the object
Priority GameObject::getPriority() {
	return priority;
}


