#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

using sf::View;

extern View view;

extern void setPlayerCoordinateForView(float x, float y);

#endif