#ifndef BASE_H
#define BASE_H

#include <iostream>

class Base {
protected:
	float x, y;
public:
	Base() {
		x = y = 0;
	}
	Base(float X, float Y):
	  x(X), y(Y) {}
	virtual float getCoordinateX();
	virtual float getCoordinateY();
	virtual void setCoordinateX(float X);
	virtual void setCoordinateY(float Y);

};

#endif