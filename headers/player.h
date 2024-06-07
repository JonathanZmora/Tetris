#ifndef __PLAYER_H
#define __PLAYER_H

#include "board.h"
#include "shape.h"
#include "point.h"

// A class to represent a player in the tetris game
class Player
{
	Board board;
	Shape currPiece;
	Point spawnLocation;
	GameConfig::eKeys keys[GameConfig::NUM_KEYS];

public:
	Player(const Point& boardTopLeft, const GameConfig::eKeys _keys[]);
	Player() {};
	virtual ~Player() {};
	bool moveDownAndCheckIfLost();
	void resumePausedGame() const;
	virtual void spawnPiece();
	virtual void executeKbhit(GameConfig::eKeys keyPressed) = 0;

protected:
	bool isKeyRelevant(GameConfig::eKeys keyPressed) const;
	const Shape& getCurrPiece() const { return currPiece; };
	const Board& getCurrBoard() const { return board; };
	int getSpawnX() const { return spawnLocation.getX(); };
	bool moveCurrPiece(GameConfig::eDirections direction) { return currPiece.move(direction); };
	bool rotateCurrPiece(GameConfig::eRotations rotation) { return currPiece.rotate(rotation); };
	void dropCurrPiece() { currPiece.drop(); };
};


#endif

