#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include "cstring.h"

using sf::Image;
using sf::Sprite;

class MovingPlatform: public Entity {
public:
	MovingPlatform(float X, float Y, int WIDTH, int HEIGHT, cString NAME, Image &image):
		Entity(X, Y, WIDTH, HEIGHT, NAME, image) {
			sprite.setTextureRect(sf::IntRect(0, 0, width, height));
			dx = 0.08;
		}
	void checkCollisionWithMap(float, float);
	void update(float&, float&);
	void control(float&, float&);
};

#endif