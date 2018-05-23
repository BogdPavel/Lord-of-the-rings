#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <list>
#include <SFML/Graphics.hpp>
#include "base.h"
#include "entity.h"
#include "enemy.h"
#include "movingPlatform.h"
#include "cstring.h"

using namespace sf;
using std::list;

const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 60;

class Map {
	static cString *TileMap;
	static int level;
	ifstream file;
	char *buffer;
	Texture textureMap;
	Sprite spriteMap;	
public:
	Map() {}
	Map(Image &image) {
		buffer = new char[MAP_WIDTH + 1]; memcpy(buffer, "", MAP_WIDTH + 1);
		TileMap = new cString[MAP_HEIGHT]();
		textureMap.loadFromImage(image);
		spriteMap.setTexture(textureMap);
	}
	void operator++ (int);
	void draw(RenderWindow &);
	static char getTileMapSymbol(int i, int j);
	static void setTileMapSymbol(int i, int j);
	static void zero(int = 0);
	void entitiesCreating(list< Entity* >& entityList, Image& enemyImage, Image& movingPlatformImage);

	~Map() {
		file.close();
		delete [] buffer;
		delete [] TileMap;
	}
};

#endif

		
