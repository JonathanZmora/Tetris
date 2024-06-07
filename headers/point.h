#ifndef __POINT_H
#define __POINT_H

#include "gameConfig.h"

// A class to represent the coordinates of a point on the console screen
class Point
{
	int x, y;

public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	int getX() const { return x; }
	int getY() const { return y; } 
	void move(GameConfig::eDirections direction);
	void draw(char ch) const;
};

#endif
