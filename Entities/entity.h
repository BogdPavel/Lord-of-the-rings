#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "base.h"
#include "cstring.h"

using sf::Sprite;
using sf::Image;
using sf::Texture;
using sf::FloatRect;

class Entity: public Base {
protected:
	float dx, dy, speed, moveTimer;
	int width, height, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	cString name;
public:
	Entity(float X, float Y, int WIDTH, int HEIGHT, cString NAME, Image &image): Base(X, Y),
		width(WIDTH), height(HEIGHT), dx(0), dy(0), moveTimer(0), speed(0), health(100),
		life(true), onGround(false), isMove(false) {
		name = NAME;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(width / 2, height / 2);
	}
	virtual void checkCollisionWithMap(float, float) = 0;
	virtual void update(float&, float&) = 0;
	virtual void control(float& time, float& currentFrame) = 0;

	virtual Sprite& getSprite();
	virtual bool getLife();
	virtual char* getName();
	virtual void setDx(float Dx);
	virtual void setHealth(int HEALTH);
	virtual FloatRect getRect();
	virtual double getDx();
	virtual int getHeight();
	virtual int getWidth();
	virtual void setHeight(int HEIGHT);
	virtual void setWidth(int WIDTH);
	virtual int getHealth();
};

#endif
