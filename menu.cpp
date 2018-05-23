#include "menu.h"

void Menu::setPosition() {
	float pos = view.getCenter().x - 400;
	for(int i = 20, j = 0; i < 150; i += 40, j++)
		menu[j].setPosition(pos + 20, i);
	info.setPosition(pos, -20);
	menuBackground.setPosition(pos + 0, 0);
	name.setPosition(pos + 15, 500);
}

void Menu::setColor() {
	for(int i = 0; i < 4; i++)
		menu[i].setColor(Color(255, 215, 0));
	name.setColor(Color(255, 215, 0));
}

void Menu::draw(RenderWindow &window) {
	window.draw(menuBackground);
	for(int i = 0; i < 4; i++)
		window.draw(menu[i]);
	window.draw(name);
}

void Menu::setNumMenu(RenderWindow &window) {
	if(IntRect(20, 20, 281, 31).contains(Mouse::getPosition(window))) {
		menu[0].setColor(Color(255, 140, 0)); numMenu = 1;
	}
	if(IntRect(20, 100, 184, 27).contains(Mouse::getPosition(window))) {
		menu[2].setColor(Color(255, 140, 0)); numMenu = 3;
	}
	if(IntRect(20, 60, 287, 33).contains(Mouse::getPosition(window))) {
		menu[1].setColor(Color(255, 140, 0)); numMenu = 2;
	}
	if(IntRect(20, 140, 116, 27).contains(Mouse::getPosition(window))) {
		menu[3].setColor(Color(255, 140, 0)); numMenu = 4;
	}
	if(IntRect(15, 500, 770, 29).contains(Mouse::getPosition(window))) {
		name.setColor(Color(255, 140, 0));
	}
}

int Menu::show(RenderWindow &window) {
	setPosition();
	while(isMenu) {
		//window.clear(Color::Black);	
		setColor();  
		numMenu = 0;
		setNumMenu(window);
		if(Mouse::isButtonPressed(Mouse::Left)) {
			switch(numMenu) {
				case 1: isMenu = false; break;
				case 3: {
						window.clear(Color(200, 193, 174));
						window.draw(info); window.display();
						while(!Keyboard::isKeyPressed(Keyboard::Escape));
						break;
						}
				case 4: window.close(); exit(1);
				case 2: { 
						Records::showRecords(window); 
						while(!Keyboard::isKeyPressed(Keyboard::Escape)); 
						break; 
						}
			}
		} 
		if(isMenu) {
			draw(window); window.display();
		}
	}
	isMenu = true;
}