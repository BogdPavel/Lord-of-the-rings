#include "entity.h"

Sprite& Entity::getSprite() {
	return sprite;
}

bool Entity::getLife() {
	return life;
}

char* Entity::getName() {
	char *temp = new char[20];
	memcpy(temp, name.str(), name.strlen() + 1);
	return temp;
}

void Entity::setDx(float Dx) {
	dx = Dx;
}

void Entity::setHealth(int HEALTH) {
	health = HEALTH;
}

FloatRect Entity::getRect() {
	return FloatRect(x, y, width, height);
}

double Entity::getDx() {
	return dx;
}

int Entity::getHeight() {
	return height;
}

int Entity::getWidth() {
	return width;
}

void Entity::setHeight(int HEIGHT) {
	height = HEIGHT;
}

void Entity::setWidth(int WIDTH) {
	width = WIDTH;
}

int Entity::getHealth() {
	return health;
}