#ifndef __BOARD_H
#define __BOARD_H

#include "point.h"

#include <vector>
using std::vector;

// A class to represent a players board in the game
class Board
{
	char board[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH] = {{}};
	Point topLeft;

public:
	Board(const Point& _topLeft);
	Board() {};
	void drawBorders() const;
	void drawBoard() const;
	void fillPoints(vector<Point> points, char ch);
	void dropPoints(size_t lowerBound, size_t leftBound, size_t rightBound);
	void dropFullRows();
	Point getTopLeft() const { return topLeft; }
	bool isPointEmpty(int x, int y) const { 
		return (board[y - topLeft.getY()][x - topLeft.getX()] == GameConfig::WHITE_SPACE); 
	}
	bool isPointInBounds(int x, int y) const;
	bool isFirstRowEmpty() const;
	size_t countFullRows() const;
	int getHighestPointY() const;
	int getNumHighestPoints() const;
};

#endif
