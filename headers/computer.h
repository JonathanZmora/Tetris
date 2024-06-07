#ifndef __COMPUTER_H
#define __COMPUTER_H

#include "move.h"
#include "player.h"
#include <vector>

using std::vector;

// A class to represent a computer player
class Computer : public Player
{
	bool wait = true;
	int offsetX = 0;
	size_t offsetRotations = 0;
	GameConfig::eLevels level;


public:
	Computer(const Point& boardTopLeft, const GameConfig::eKeys _keys[], GameConfig::eLevels _level) :
		Player(boardTopLeft, _keys), level(_level) {}

	Computer() {}

	void spawnPiece() override;
	void executeKbhit(GameConfig::eKeys keyPressed) override;

private:
	void findBestMove();
	void addMoves(vector<Move>& moves, Board& currBoard, Shape& currPiece, size_t rotation) const;
	void rotateAndMoveToTopRight(Shape& currPiece) const;
	size_t getRandNum() const;
	Move compareMoves(const vector<Move>& moves) const;
};

#endif 
