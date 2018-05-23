#include "camera.h"

View view(sf::FloatRect(0, 0, 800, 576));

void setPlayerCoordinateForView(float x, float y) {
	float tempX, tempY = 288;
	if(x < 400) tempX = 400;
	if(x >= 400 && x <= 1520) tempX = x;
	if(x > 1520) tempX = 1520;
	view.setCenter(tempX, tempY);
}