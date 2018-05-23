#include "movingPlatform.h"

void MovingPlatform::update(float& time, float& currentFrame) {
	x += dx*time;
	checkCollisionWithMap(dx, 0);
	sprite.setPosition(x + width / 2, y + height / 2);
}

void MovingPlatform::control(float& , float&) {
	return;
}

void MovingPlatform::checkCollisionWithMap(float Dx, float Dy) {
	for (int i = y / 32; i < (y + height) / 32; i++)//проходимся по тайликам, контактирующим с игроком
		for (int j = x / 32; j < (x + width) / 32; j++) {
			if(Map::getTileMapSymbol(i, j) == 'b' || Map::getTileMapSymbol(i, j) == 'g' || Map::getTileMapSymbol(i, j) == '4') {
				if(Dx > 0) {
					x = j * 32 - width; dx = -0.1;
				}
				if(Dx < 0) {
					x = j * 32 + 32; dx = 0.1;
				}
			}
	}
}