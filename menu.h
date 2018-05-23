#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "records.h"
#include "camera.h"

using namespace sf;

class Menu {
	Sprite menu[4], info, menuBackground, name;
	Texture menuTexture[4], infoTexture, menuBackgroundTexture, nameTexture;
	bool isMenu;
	int numMenu;
	void setPosition();
	void setColor();
	void draw(RenderWindow &window);
	void setNumMenu(RenderWindow &window);
public:
	Menu(): isMenu(1), numMenu(0) {
		menuTexture[0].loadFromFile("images/NG.png");
		menuTexture[2].loadFromFile("images/Ab.png");
		menuTexture[3].loadFromFile("images/Ex.png");
		menuTexture[1].loadFromFile("images/Rec.png");
		infoTexture.loadFromFile("images/informationBackground.png");
		menuBackgroundTexture.loadFromFile("images/MB4.png");
		nameTexture.loadFromFile("images/Name.png");
		for(int i = 0; i < 4; i++)
			menu[i].setTexture(menuTexture[i]);
		info.setTexture(infoTexture), menuBackground.setTexture(menuBackgroundTexture), name.setTexture(nameTexture);

	}
	int show(RenderWindow &window);
};

#endif