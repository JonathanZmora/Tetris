#ifndef __MOVE_H
#define __MOVE_H

// A class to represent a possible move for a piece in the tetris game
class Move
{
	size_t fullRows;
	size_t highestPoint;
	size_t numHighestPoints;
	size_t offsetX;
	size_t offsetRotations;

public:
	Move(size_t _fullRows, size_t _highestPoint, size_t _numHighestPoints, size_t _offsetX, size_t _offsetRotations) :
		fullRows(_fullRows), highestPoint(_highestPoint),
		numHighestPoints(_numHighestPoints), offsetX(_offsetX), offsetRotations(_offsetRotations) {}

	Move() {};

	size_t getNumFullRows() const { return fullRows; }
	size_t getHighestPoint() const { return highestPoint; }
	size_t getNumHighestPoints() const { return numHighestPoints; }
	size_t getOffsetX() const { return offsetX; }
	size_t getOffsetRotations() const { return offsetRotations; }
};

#endif

