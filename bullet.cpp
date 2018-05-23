#include "bullet.h"

void Bullet::update(float& time, float& currentFrame) {
	switch (direction) {
		case 0: dx = -speed; break;//интовое значение state = left
		case 1: dx = speed; break;//интовое значение state = right
		default: dx = speed; break;
	}	
	x += dx*time;
 
	if(x <= 0) life = false;
	if(x >= 1920) life = false;
	if(health <= 0) life = false;	
	checkCollisionWithMap(time, currentFrame);
	sprite.setPosition(x + width, y + height + 10);
}

void Bullet::checkCollisionWithMap(float , float ) {
	for (int i = y / 32; i < (y + height) / 32; i++)//проходимся по тайликам, контактирующим с игроком
		for (int j = x / 32; j < (x + width) / 32; j++) 
			if(Map::getTileMapSymbol(i, j) == 'b' ) {
				life = false;
			}
}

