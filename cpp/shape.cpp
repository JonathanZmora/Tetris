#include "shape.h"
#include <Windows.h>

// Constructor
Shape::Shape(const Point& centerPoint, Board* _board, GameConfig::ePieces _pieceType) 
	: board(_board), pieceType(_pieceType)
{
	if (pieceType == GameConfig::ePieces::BOMB)
		body.push_back(centerPoint);
	else
	{
		body = vector<Point>(GameConfig::NUM_POINTS_IN_SHAPE, centerPoint);

		switch (pieceType) // calls the appropriate init function based on the given piece type
		{
		case GameConfig::ePieces::I_SHAPE:
			initShapeI();
			break;
		case GameConfig::ePieces::T_SHAPE:
			initShapeT();
			break;
		case GameConfig::ePieces::Z_SHAPE:
			initShapeZ();
			break;
		case GameConfig::ePieces::L_SHAPE:
			initShapeL();
			break;
		case GameConfig::ePieces::J_SHAPE:
			initShapeJ();
			break;
		case GameConfig::ePieces::S_SHAPE:
			initShapeS();
			break;
		case GameConfig::ePieces::B_SHAPE:
			initShapeB();
			break;
		default:
			break;
		}
	}
}

// A method that draws the shape on the console screen
void Shape::draw() const
{
	for (const Point& p : body)
	{
		if (pieceType == GameConfig::ePieces::BOMB)
			p.draw(GameConfig::BOMB_CHAR);
		else
			p.draw(GameConfig::PIECE_CHAR);
	}
}

// A method that moves the shape in the given direction on the console screen,
// and returns true if the move was executed and false if it cannot be executed
bool Shape::move(GameConfig::eDirections direction)
{
	if (!checkMoveValid(direction))
		return false;

	for (Point& p : body) // moves the piece to the new location
	{
		p.draw(GameConfig::WHITE_SPACE);
		p.move(direction);
	}

	this->draw(); // draws the piece in the new location
	return true;
}

// A method that moves the shape in the given direction without printing the changes to the
// console screen. Returns true if the move was executed and false if it cannot be executed.
bool Shape::moveAndDontDraw(GameConfig::eDirections direction)
{
	if (!checkMoveValid(direction))
		return false;

	for (Point& p : body)
		p.move(direction);

	return true;
}

// A method that calculates the coordinates of the shapes body after rotating in the
// given rotation direction and stores the rotated points in the given rotatedPoints vector.
bool Shape::getRotatedPoints(vector<Point>& rotatedPoints, GameConfig::eRotations rotation) const
{
	int dx, dy, newX, newY;

	for (const Point& p : body)
	{
		dx = p.getX() - body[1].getX();
		dy = p.getY() - body[1].getY();

		if (rotation == GameConfig::eRotations::CLOCKWISE)
		{
			newX = body[1].getX() - dy;
			newY = body[1].getY() + dx;
		}
		else
		{
			newX = body[1].getX() + dy;
			newY = body[1].getY() - dx;
		}

		if (!board->isPointInBounds(newX, newY) || !board->isPointEmpty(newX, newY))
			return false;

		Point newPoint(newX, newY);
		rotatedPoints.push_back(newPoint);
	}

	return true;
}

// A method that rotates the piece according to the given rotation direction
bool Shape::rotate(GameConfig::eRotations rotation)
{
	if (pieceType == GameConfig::ePieces::B_SHAPE || pieceType == GameConfig::ePieces::BOMB)
		return true;

	vector<Point> rotatedPoints;

	if (!getRotatedPoints(rotatedPoints, rotation))
		return false;

	for (size_t i = 0; i < body.size(); i++)
	{
		body[i].draw(GameConfig::WHITE_SPACE);
		body[i] = rotatedPoints[i];
	}

	this->draw();
	return true;
}

// A method that rotates the piece according to the given rotation 
// direction without printing the changes to the console screen.
bool Shape::rotateAndDontDraw(GameConfig::eRotations rotation)
{
	if (pieceType == GameConfig::ePieces::B_SHAPE || pieceType == GameConfig::ePieces::BOMB)
		return true;

	vector<Point> rotatedPoints;

	if (!getRotatedPoints(rotatedPoints, rotation))
		return false;

	body = rotatedPoints;

	return true;
}

// A method that drops the piece quickly until it hits the bottom of the board or another piece.
void Shape::drop()
{
	while (canMoveDown())
	{
		move(GameConfig::eDirections::DOWN);
		Sleep(20);
	}
}

// A method that explodes a bomb when called by a bomb shape.
void Shape::explode()
{
	if (pieceType != GameConfig::ePieces::BOMB)
		return;

	vector<Point> pointsInRange;
	Point start(body[0].getX() - 4, body[0].getY() - 4), end(body[0].getX() + 4, body[0].getY() + 4), temp;
	size_t lowerBound, upperBound, leftBound, rightBound;

	while (start.getX() < board->getTopLeft().getX())
		start.move(GameConfig::eDirections::RIGHT);

	while (start.getY() < board->getTopLeft().getY())
		start.move(GameConfig::eDirections::DOWN);

	while (end.getX() > board->getTopLeft().getX() + GameConfig::GAME_WIDTH - 1)
		end.move(GameConfig::eDirections::LEFT);

	while (end.getY() > board->getTopLeft().getY() + GameConfig::GAME_HEIGHT - 1)
		end.move(GameConfig::eDirections::UP);

	upperBound = start.getY() - board->getTopLeft().getY();
	leftBound = start.getX() - board->getTopLeft().getX();
	lowerBound = end.getY() - board->getTopLeft().getY();
	rightBound = end.getX() - board->getTopLeft().getX();

	for (size_t row = upperBound; row <= lowerBound; ++row)
	{
		temp = start;

		for (size_t col = leftBound; col <= rightBound; ++col)
		{
			pointsInRange.push_back(temp);
			temp.move(GameConfig::eDirections::RIGHT);
		}

		start.move(GameConfig::eDirections::DOWN);
	}

	board->fillPoints(pointsInRange, GameConfig::WHITE_SPACE);
	board->dropPoints(upperBound - 1, leftBound, rightBound);
}

// A method that returns true if the shape can move right, false otherwise.
bool Shape::canMoveRight() const
{
	for (const Point& p : body)
		if (!board->isPointInBounds(p.getX() + 1, p.getY()) ||
			!board->isPointEmpty(p.getX() + 1, p.getY()))
			return false;
	return true;
}

// A method that returns true if the shape can move left, false otherwise.
bool Shape::canMoveLeft() const
{
	for (const Point& p : body)
		if (!board->isPointInBounds(p.getX() - 1, p.getY()) ||
			!board->isPointEmpty(p.getX() - 1, p.getY()))
			return false;
	return true;
}

// A method that returns true if the shape can move down, false otherwise.
bool Shape::canMoveDown() const
{
	for (const Point& p : body)
		if (!board->isPointInBounds(p.getX(), p.getY() + 1) ||
			!board->isPointEmpty(p.getX(), p.getY() + 1))
			return false;
	return true;
}

// A method that returns true if the shape can move up, false otherwise.
bool Shape::canMoveUp() const
{
	for (const Point& p : body)
		if (!board->isPointInBounds(p.getX(), p.getY() - 1) ||
			!board->isPointEmpty(p.getX(), p.getY() - 1))
			return false;
	return true;
}

// A method that returns true if the shape can move in the given direction, false otherwise.
// in the case where the the move direction is down and the shape cannot move, if the shape
// is a bomb it will explode, otherwise it will be written to the board in the current location.
bool Shape::checkMoveValid(GameConfig::eDirections direction)
{
	switch (direction) // based on the given direction, checks if the new location is valid
	{
	case GameConfig::eDirections::LEFT:
		if (!canMoveLeft())
			return false;
		break;
	case GameConfig::eDirections::RIGHT:
		if (!canMoveRight())
			return false;
		break;
	case GameConfig::eDirections::UP:
		if (!canMoveUp())
			return false;
		break;
	case GameConfig::eDirections::DOWN:
		if (!canMoveDown())
		{
			if (pieceType == GameConfig::ePieces::BOMB)
				explode();
			else
				board->fillPoints(body, GameConfig::PIECE_CHAR);
			return false;
		}
		break;
	default:
		break;
	}

	return true;
}

// A method to initialize the points for an I piece
void Shape::initShapeI()
{
	body[0].move(GameConfig::eDirections::LEFT);
	body[2].move(GameConfig::eDirections::RIGHT);
	body[3] = body[2];
	body[3].move(GameConfig::eDirections::RIGHT);
}

// A method to initialize the points for a T piece
void Shape::initShapeT()
{
	body[0].move(GameConfig::eDirections::LEFT);
	body[2].move(GameConfig::eDirections::RIGHT);
	body[3].move(GameConfig::eDirections::DOWN);
}

// A method to initialize the points for a Z piece
void Shape::initShapeZ()
{
	body[0].move(GameConfig::eDirections::LEFT);
	body[2].move(GameConfig::eDirections::DOWN);
	body[3] = body[2];
	body[3].move(GameConfig::eDirections::RIGHT);
}

// A method to initialize the points for an L piece
void Shape::initShapeL()
{
	body[1].move(GameConfig::eDirections::DOWN);
	body[2] = body[1];
	body[2].move(GameConfig::eDirections::DOWN);
	body[3] = body[2];
	body[3].move(GameConfig::eDirections::RIGHT);
}

// A method to initialize the points for a J piece
void Shape::initShapeJ()
{
	body[1].move(GameConfig::eDirections::DOWN);
	body[2] = body[1];
	body[2].move(GameConfig::eDirections::DOWN);
	body[3] = body[2];
	body[3].move(GameConfig::eDirections::LEFT);
}

// A method to initialize the points for an S piece
void Shape::initShapeS()
{
	body[1].move(GameConfig::eDirections::DOWN);
	body[0] = body[1];
	body[0].move(GameConfig::eDirections::LEFT);
	body[2] = body[1];
	body[2].move(GameConfig::eDirections::UP);
	body[3] = body[2];
	body[3].move(GameConfig::eDirections::RIGHT);
}

// A method to initialize the points for a Box piece
void Shape::initShapeB()
{
	body[0].move(GameConfig::eDirections::LEFT);
	body[2].move(GameConfig::eDirections::DOWN);
	body[3] = body[2];
	body[3].move(GameConfig::eDirections::LEFT);
}

// A method that returns the highest points Y value in the shapes body.
int Shape::getHighestPointY() const
{
	int minY = GameConfig::BOARDS_Y + GameConfig::GAME_HEIGHT;

	for (const Point& p : body)
		if (p.getY() < minY)
			minY = p.getY();

	return minY;
}

// A method that returns the number of points in the shapes body with the highest Y value.
int Shape::getNumHighestPoints() const
{
	int counter = 0, highestPointY = getHighestPointY();

	for (const Point& p : body)
		if (p.getY() == highestPointY)
			++counter;

	return counter;
}
