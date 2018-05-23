#include "map.h"

cString* Map::TileMap;

int Map::level = 0;

void Map::operator++ (int) {
	level++;
	memcpy(buffer, (string("Level") + to_string((long long int)level) + string(".txt")).c_str(), 11);
	file.open(buffer, ios::in);
	if(!file) exit(1);
	int i = 0;
	while(i < MAP_HEIGHT) {
		file.getline(buffer, MAP_WIDTH + 1);
		TileMap[i] = buffer;
		i++;
	}
}

void Map::entitiesCreating(list< Entity* >& entityList, Image& enemyImage, Image& movingPlatformImage) {
	int number_of_enemies;
	file.getline(buffer, 5); number_of_enemies = atoi(buffer);
	Base *array_of_enemies = new Base[number_of_enemies]();
	int i = 0;
	while(i < number_of_enemies) {
		file.getline(buffer, 5); array_of_enemies[i].setCoordinateX(atoi(buffer));
		file.getline(buffer, 5); array_of_enemies[i].setCoordinateY(atoi(buffer));
		if(i < number_of_enemies - 1)
			entityList.push_back(new Enemy(array_of_enemies[i].getCoordinateX(), array_of_enemies[i].getCoordinateY(), 32, 40, "EasyEnemy", enemyImage));
		if(i == number_of_enemies - 1)
			entityList.push_back(new Enemy(array_of_enemies[i].getCoordinateX(), array_of_enemies[i].getCoordinateY(), 32, 40, "HardEnemy", enemyImage));
		i++;
	}
	int number_of_movingPlatforms;
	file.getline(buffer, 5); number_of_movingPlatforms = atoi(buffer);
	Base *array_of_movingPlatforms = new Base[number_of_movingPlatforms]();
	i = 0;
	while(i < number_of_movingPlatforms) {
		file.getline(buffer, 5); array_of_movingPlatforms[i].setCoordinateX(atoi(buffer));
		file.getline(buffer, 5); array_of_movingPlatforms[i].setCoordinateY(atoi(buffer));
		entityList.push_back(new MovingPlatform(array_of_movingPlatforms[i].getCoordinateX(), array_of_movingPlatforms[i].getCoordinateY(), 95, 22, "MovingPlatform", movingPlatformImage));
		i++;
	}
	file.close();
}

void Map::draw(RenderWindow &window) {
for(int i = 0; i < MAP_HEIGHT; i++)
	for(int j = 0;  j < MAP_WIDTH; j++) {
		if(TileMap[i][j] == ' ')
			spriteMap.setTextureRect(IntRect(0, 256, 0, 0)); 
		if(TileMap[i][j] == 'b') 
			spriteMap.setTextureRect(IntRect(32, 96, 32, 32));
		if(TileMap[i][j] == '1') 
			spriteMap.setTextureRect(IntRect(320, 96, 32, 32));
		if(TileMap[i][j] == '2') 
			spriteMap.setTextureRect(IntRect(352, 96, 32, 32));
		if(TileMap[i][j] == '3') 
			spriteMap.setTextureRect(IntRect(480, 96, 32, 32));
		if(TileMap[i][j] == '4') 
			spriteMap.setTextureRect(IntRect(512, 96, 32, 32));
		if(TileMap[i][j] == 'l') 
			spriteMap.setTextureRect(IntRect(192, 0, 32, 32));
		if(TileMap[i][j] == 'r') 
			spriteMap.setTextureRect(IntRect(128, 0, 32, 32));
		if(TileMap[i][j] == 'g') 
			spriteMap.setTextureRect(IntRect(160, 32, 32, 32));
		if(TileMap[i][j] == 's') 
			spriteMap.setTextureRect(IntRect(160, 0, 32, 32));
		if(TileMap[i][j] == 'f') 
			spriteMap.setTextureRect(IntRect(128, 32, 32, 32));
		if(TileMap[i][j] == 'u') 
			spriteMap.setTextureRect(IntRect(224, 256, 32, 32));
		if(TileMap[i][j] == 'h') 
			spriteMap.setTextureRect(IntRect(128, 256, 32, 32));
		if(TileMap[i][j] == 'p') 
			spriteMap.setTextureRect(IntRect(192, 256, 32, 10));
		if(TileMap[i][j] == 'n') 
			spriteMap.setTextureRect(IntRect(160, 256, 32, 32));
		if(TileMap[i][j] == 'o') 
			spriteMap.setTextureRect(IntRect(104, 268, 11, 11));
		spriteMap.setPosition(j * 32, i *32);
		window.draw(spriteMap);
	}
}

void Map::zero(int value) {
	level = value;
}

char Map::getTileMapSymbol(int i, int j) {
	return TileMap[i][j];
}

void Map::setTileMapSymbol(int i, int j) {
	TileMap[i][j] = ' ';
}