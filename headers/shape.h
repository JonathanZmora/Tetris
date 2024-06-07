#ifndef __SHAPE_H
#define __SHAPE_H

#include "point.h"
#include "board.h"

#include <vector>
using std::vector;

// A class to represent a falling piece in the tetris game 
class Shape
{
	vector<Point> body;
	Board* board;
	GameConfig::ePieces pieceType;

public:
	Shape(const Point& centerPoint, Board* _board, GameConfig::ePieces _pieceType);
	Shape() { board = nullptr; pieceType = GameConfig::ePieces::NONE; } // default constructor
	void setBoard(Board* _board) { board = _board; }
	void draw() const;
	bool move(GameConfig::eDirections direction);
	bool moveAndDontDraw(GameConfig::eDirections direction);
	bool rotate(GameConfig::eRotations rotation);
	bool rotateAndDontDraw(GameConfig::eRotations rotation);
	void drop();
	GameConfig::ePieces getPieceType() const { return pieceType; }
	int getHighestPointY() const;
	int getNumHighestPoints() const;
	int getCenterX() const {
		if (pieceType == GameConfig::ePieces::BOMB)	return body[0].getX();
		else return body[1].getX();
	}

private:
	bool getRotatedPoints(vector<Point>& rotatedPoints, GameConfig::eRotations rotation) const;
	bool checkMoveValid(GameConfig::eDirections direction);
	bool canMoveRight() const;
	bool canMoveLeft() const;
	bool canMoveDown() const;
	bool canMoveUp() const;
	void explode();
	void initShapeI();
	void initShapeJ();
	void initShapeL();
	void initShapeT();
	void initShapeZ();
	void initShapeS();
	void initShapeB();
};

#endif

