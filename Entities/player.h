#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "enemy.h"
#include "map.h"
#include "camera.h"
#include "cstring.h"

using sf::Sprite;
using sf::Image;
using std::list;

class Player: public Entity {
	static int score;
	enum {left, right, up, down, jump, stay} state;
	bool onLadder;
public:
	bool isShoot;
	Player(float X, float Y, int WIDTH, int HEIGHT, cString NAME, Image &image):
		Entity(X, Y, WIDTH, HEIGHT, NAME, image) {
		state = stay;
		onLadder = false;
		if( name == "Player1")
			sprite.setTextureRect(IntRect(32, 0, width, height));
	}
	void checkCollisionWithMap(float, float);
	void update(float&, float&);
	void control(float&, float&);
	void setStartCoordinateXY();
	void entitiesCollision(list< Entity* >& , list< Entity* >::iterator& , float );
	void setScore(int value);
	int getState();
	int getScore();
};

#endif