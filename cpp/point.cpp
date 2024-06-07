#include "point.h"
#include "general.h"

#include <iostream>
using namespace std;

// A method that gets a direction and moves the point in the given direction
void Point::move(GameConfig::eDirections direction)
{
	switch (direction)
	{
	case GameConfig::eDirections::LEFT:
		this->x--;
		break;
	case GameConfig::eDirections::RIGHT:
		this->x++;
		break;
	case GameConfig::eDirections::DOWN:
		this->y++;
		break;
	case GameConfig::eDirections::UP:
		this->y--;
		break;
	default:
		break;
	}
}

// A method that draws the given character in the point on the console screen
void Point::draw(char ch) const
{
	gotoxy(this->x, this->y);
	cout << ch;
}
