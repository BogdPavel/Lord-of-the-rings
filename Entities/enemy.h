#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include "cstring.h"

using sf::Sprite;
using sf::Image;

class Enemy: public Entity {
public:
	Enemy(float X, float Y, int WIDTH, int HEIGHT, cString NAME, Image &image):
		Entity(X, Y, WIDTH, HEIGHT, NAME, image) {
		if(name == "EasyEnemy") {
			sprite.setTextureRect(sf::IntRect(290, 192, width, height));
			dx = 0.1;
		}
		if(name == "HardEnemy") {
			sprite.setTextureRect(sf::IntRect(290, 242, width, height));
		}
	}
	void checkCollisionWithMap(float, float);
	void update(float&, float&);
	void control(float&, float&);
};

#endif