#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include "cstring.h"

using sf::Sprite;
using sf::Image;

class Bullet: public Entity {
	int direction;
public:
	Bullet(float X, float Y, int WIDTH, int HEIGHT, cString NAME, Image &image, int DIRECTION):
	  Entity(X, Y, WIDTH, HEIGHT, NAME, image) {
		direction = DIRECTION;
		speed = 0.8;
		life = true;
	}
	void checkCollisionWithMap(float, float);
	void update(float&, float&);
	void control(float&, float&) {
		return;
	}
};

#endif