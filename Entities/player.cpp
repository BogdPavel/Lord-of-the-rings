#include "player.h"

int Player::score = 0;

void Player::update(float& time, float& currentFrame) {
	if(life)
		control(time, currentFrame);
	switch(state) {
		case right: dx = speed; break;
		case left: dx = -speed; break;
		case up:  dy = -speed; break;
		case down: dy = speed; break;
		case jump:  break;
		case stay:  break;
	}
	x += dx*time;
	checkCollisionWithMap(dx, 0);
	y += dy*time;
	checkCollisionWithMap(0, dy);
	if(!isMove) speed = 0;
	if(health <= 0) {
		setPlayerCoordinateForView(400, 288);
		life = false;
		health = 0;
		speed = 0;
	}
	sprite.setPosition(x + width / 2, y + height / 2 + 8); //задаем позицию спрайта в место его центра
	setPlayerCoordinateForView(x, y);
	if(!onLadder) {
		dy += 0.0015*time; //делаем притяжение к земле
	}
}

void Player::control(float& time, float& currentFrame) {
	if(Keyboard::isKeyPressed(Keyboard::Up) && onLadder) {
		speed = 0.1; state = up;
		currentFrame += time*0.0015;
		if(currentFrame > 3) currentFrame -= 3;	
		sprite.setTextureRect(IntRect(32*int(currentFrame), 147, 32, 49)); 
	}
	if(Keyboard::isKeyPressed(Keyboard::Up) && onGround && !onLadder) {
		dy = -0.5; state = jump; onGround = false;
	}
	if(Keyboard::isKeyPressed(Keyboard::Down) && onLadder) {
		speed = 0.1; state = down;
		currentFrame += time*0.0015;
		if(currentFrame > 3) currentFrame -= 3;	
		sprite.setTextureRect(IntRect(32*int(currentFrame), 147, 32, 49)); 
	}
	if(Keyboard::isKeyPressed(Keyboard::Down) && onGround &&!onLadder) {
		state = down;
	}
	if(Keyboard::isKeyPressed(Keyboard::Left)) {
		speed = 0.1; state = left;
		currentFrame += time*0.0015;
		if(currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(IntRect(32*int(currentFrame), 49, 32, 49));
		setPlayerCoordinateForView(x, y);
	}
	if(Keyboard::isKeyPressed(Keyboard::Right)) {
		speed = 0.1; state = right;
		currentFrame += time*0.0015;
		if(currentFrame > 3) currentFrame -= 3;	
		sprite.setTextureRect(IntRect(32*int(currentFrame), 98, 32, 49));
		setPlayerCoordinateForView(x, y);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && onGround && !onLadder ) {
		isShoot = true;
	}
	onLadder = false;
	onGround = false;
}

void Player::checkCollisionWithMap(float Dx, float Dy) {
	if(y < 0) y = 0;
	int flag = 0;
	for (int i = y / 32; i < (y + height) / 32; i++)//проходимся по тайликам, контактирующим с игроком
		for (int j = x / 32; j < (x + width) / 32; j++) {

			if(Map::getTileMapSymbol(i, j) == 'b' || Map::getTileMapSymbol(i, j) == 's' || Map::getTileMapSymbol(i, j) == '1' || Map::getTileMapSymbol(i, j) == 'g' ||
				Map::getTileMapSymbol(i, j) == 'r' || Map::getTileMapSymbol(i, j) == '2' || Map::getTileMapSymbol(i, j) == 'l' || Map::getTileMapSymbol(i, j) == 'p') {
				if(Dy > 0) { y = i * 32 - height; dy = 0; onGround = true; }
				if(Dy < 0) { y = i * 32 + 32; dy = 0;}
				if(Dx > 0) { x = j * 32 - width; }
				if(Dx < 0) { x = j * 32 + 32; }
			}

			/*if(Map::getTileMapSymbol(i, j) == 'f'){
				health -= 40;
				Map::setTileMapSymbol(i, j);
			}*/
			if(Map::getTileMapSymbol(i, j) == 't') {
				health += 20;
				Map::setTileMapSymbol(i, j);
			}
			if(Map::getTileMapSymbol(i, j) == 'u') {
				if(Dy > 0 || Dy < 0)
					dy = 0;
				onLadder = true;
				onGround = true;
			}
			if(Map::getTileMapSymbol(i, j) == 'f'&& Dy > 0 && !flag) {
				health -= 40;
				dy = -0.6;
				onGround = false;
				flag++;
			}
			if(Map::getTileMapSymbol(i, j) == 'o') {
				score += 10;
				Map::setTileMapSymbol(i, j);
			}
			/*if(Map::getTileMapSymbol(i, j) == 'n') {
				health -= 40;
				dy = -0.2;
				onGround = false;
			}*/
		}

}

void Player::entitiesCollision(list< Entity* >& entityList, list< Entity* >::iterator& entityIterator, float time) {
	list< Entity* >::iterator it = entityList.begin();
	for (entityIterator = entityList.begin(); entityIterator != entityList.end(); entityIterator++) {//проходимся по эл-там списка
		
		if ((*entityIterator)->getRect().intersects(this->getRect())) {//если прямоугольник спрайта объекта пересекается с игроком				

			if (!strcmp((*entityIterator)->getName(), "MovingPlatform")) {
				if (dy > 0 || !onGround) {//при этом игрок находится в состоянии после прыжка, т.е падает вниз
					if (y + height < (*entityIterator)->getCoordinateY() + (*entityIterator)->getHeight()) { //если игрок находится выше платформы, т.е это его ноги минимум (тк мы уже проверяли что он столкнулся с платформой)
						y = (*entityIterator)->getCoordinateY() - height + 3; 
						x += ((*entityIterator)->getDx()) * time ; 
						speed = 0; dy = speed;
						onGround = true; // то выталкиваем игрока так, чтобы он как бы стоял на платформе
						continue;
					}
				}
			}

			if (!strcmp((*entityIterator)->getName(), "EasyEnemy") || !strcmp((*entityIterator)->getName(), "HardEnemy")) {
				if (dy > 0 && onGround == false) {
					(*entityIterator)->setDx(0); speed = -0.2; dy = speed; (*entityIterator)->setHealth(0); 
				}
				else {
					health -= 5;
				}
			}
			if(!strcmp((*entityIterator)->getName(), "EnemyBullet")) {
				health -= 50;
				(*entityIterator)->setHealth(0);
			}
		}
		if (!strcmp((*entityIterator)->getName(), "EasyEnemy") || !strcmp((*entityIterator)->getName(), "HardEnemy")) {
			it = entityIterator;
			for(it; it != entityList.end(); it++) {
				if ((*entityIterator)->getRect().intersects((*it)->getRect()) && !strcmp((*it)->getName(), "PlayerBullet")) {
					this->setScore(40);
					(*entityIterator)->setHealth(0);
					(*it)->setHealth(0);
				}
			}
		}
	}

}

void Player::setStartCoordinateXY() {
	x = 80;
	y = 440;
}

int Player::getState() {
	return state;
}

int Player::getScore() {
	return score;
}

void Player::setScore(int value) {
	this->score += value;
}


