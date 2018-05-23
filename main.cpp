#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>
#include <sstream>
#include <list>
#include <SFML/Graphics.hpp>
#include "cstring.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "movingPlatform.h"					//экран - 800*575, карта - 40*18, камера - 800*575
#include "menu.h"
#include "map.h"
#include "camera.h"

using namespace sf;
using std::list;
using std::string;

int game(Image& mapImage, RenderWindow& window);
 
int main() {

	RenderWindow window(VideoMode(800, 576), "Lord of the Rings"); 
	Image mapImage; mapImage.loadFromFile("images/taily_map.png");
	Menu gameMenu; gameMenu.show(window);
	while(1) {
		if(game(mapImage, window)) {
		}
		else gameMenu.show(window);
	}
	return 0;
}

int game(Image& mapImage, RenderWindow& window) {
	Map Level(mapImage); Level++;
	Font font; font.loadFromFile("Applications/a_font_with_serifs.ttf");
	Text scoreText("", font, 25); scoreText.setColor(Color::Red); scoreText.setStyle(Text::Bold);
	
	Text buffer("", font, 30); buffer.setColor(Color(255, 215, 0)); buffer.setStyle(Text::Bold);
	String str;
	Text playerNameText(str, font, 40); playerNameText.setColor(Color::Red); playerNameText.setStyle(Text::Bold);

	Image backgroundImage; backgroundImage.loadFromFile("images/background0.png");
	Texture backgroundTexture; backgroundTexture.loadFromImage(backgroundImage);
	Sprite backgroundSprite; backgroundSprite.setTexture(backgroundTexture);

	Image playerImage; playerImage.loadFromFile("images/players11.png");
	Player player(70, 240, 32, 49, "Player1", playerImage);

	list< Entity* > entityList;
	list< Entity* >::iterator entityIterator;

	Image enemyImage; enemyImage.loadFromFile("images/players.png");
	Image movingPlatformImage; movingPlatformImage.loadFromFile("images/movingPlatform.png"); 

	Image bulletImage; bulletImage.loadFromFile("images/bullet.png"); bulletImage.createMaskFromColor(Color(0, 0, 0));

	Level.entitiesCreating(entityList, enemyImage, movingPlatformImage);

	Clock clock, gameTimeClock;	
	float currentFrame = 0, bulletTime = 0;
	int gameTime = 0, flag = 0;

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asMicroseconds();
		if(player.getLife()) (int)gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time/800;
		bulletTime += time;
		Event event;

		while (window.pollEvent(event)) {
			switch(event.type) {
			case Event::Closed:
				window.close(); 
				break;
			case Event::TextEntered:
				if(event.text.unicode >= 32 && event.text.unicode <= 126)
					str += static_cast< char >(event.text.unicode);
				else if(event.text.unicode == 8 && str.getSize() > 0)
					str.erase(str.getSize() - 1, str.getSize());
				playerNameText.setString(str);
				playerNameText.setPosition(view.getCenter().x + 50, 258);
				if(event.text.unicode == 13) {
					Records::setResult(str, player.getScore(), gameTime);
					Level.zero();
					return 0;
				}
				break;
			}

			if (player.isShoot == true) { 
				player.isShoot = false; 
				entityList.push_back(new Bullet(player.getCoordinateX(), player.getCoordinateY(), 16, 16, "PlayerBullet", bulletImage, player.getState())); 
			}
			
		}
		for (entityIterator = entityList.begin(); entityIterator != entityList.end(); ) {
			Entity *b = *entityIterator;
			b->update(time, currentFrame);
			if(!strcmp(b->getName(), "HardEnemy") && bulletTime > 3000) {
				entityList.push_back(new Bullet(b->getCoordinateX(), b->getCoordinateY(), 16, 16, "EnemyBullet", bulletImage, 0));
				bulletTime = 0;
			}
			if (b->getLife() == false) { 
				entityIterator = entityList.erase(entityIterator); delete b; 
			}
			else entityIterator++;
		}

		player.update(time, currentFrame);
		player.entitiesCollision(entityList, entityIterator, time);
		
		window.setView(view);
		window.clear(Color::White);
		
		ostringstream playerScoreString, playerHealthString, playerTimeString;
		playerScoreString << player.getScore(); playerHealthString << player.getHealth(); playerTimeString << gameTime;
		scoreText.setString("Score - " + playerScoreString.str() + " " + "Health - " + playerHealthString.str() + " " + 
			"Time - " + playerTimeString.str());
		scoreText.setPosition(view.getCenter().x - 350, view.getCenter().y - 280); 

		window.draw(backgroundSprite);
		Level.draw(window);
		window.draw(scoreText);
		window.draw(player.getSprite());
		
		for (entityIterator = entityList.begin(); entityIterator != entityList.end(); entityIterator++) { 
			window.draw((*entityIterator)->getSprite());
		}

		if (player.getHealth() <= 0) {
			window.clear(Color(200, 193, 174));
			buffer.setString("Enter your name: "); 
			buffer.setPosition(view.getCenter().x - 150, 268); window.draw(buffer);
			window.draw(playerNameText);
		}

		if(player.getCoordinateX() > 1750 && player.getCoordinateY() < 60)
			return 1;
		window.display();
	}
}