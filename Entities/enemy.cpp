#include "enemy.h"

void Enemy::checkCollisionWithMap(float Dx, float Dy) {
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

void Enemy::update(float& time, float& currentFrame) {
	control(time, currentFrame);
	x += dx*time;
	checkCollisionWithMap(dx, 0);
	sprite.setPosition(x + width / 2, y + height / 2);
	if (health <= 0){ life = false; }
}

void Enemy::control(float& time, float& currentFrame) {
	if(dx < 0) {
		currentFrame += time*0.003;
		if(currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(IntRect(290 + 32*int(currentFrame), 245, 32, 40));
	}
	if(dx > 0) {
		currentFrame += time*0.003;
		if(currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(IntRect(290 + 32*int(currentFrame), 293, 32, 40));
	}
}



