#include "computer.h"

#include <iostream>

using std::vector;
using std::rand;

// A method that finds the best move for the computer players current piece 
// and updates the offsetX and offsetRotations data members accordingly
void Computer::findBestMove()
{
	Board currBoard = getCurrBoard();
	Shape currPiece = getCurrPiece();
	Move bestMove;
	vector<Move> moves;

	currPiece.setBoard(&currBoard);

	if (getRandNum() == 0) 
	{
		offsetX = (rand() % GameConfig::GAME_WIDTH) - GameConfig::GAME_WIDTH / 2;
		offsetRotations = rand() % GameConfig::NUM_ROTATIONS;
		return;
    }

	while (currPiece.moveAndDontDraw(GameConfig::eDirections::RIGHT));

	for (size_t rotation = 0; rotation < GameConfig::NUM_ROTATIONS; ++rotation)
	{
		addMoves(moves, currBoard, currPiece, rotation);
		rotateAndMoveToTopRight(currPiece);
	}

	bestMove = compareMoves(moves);
	offsetX = bestMove.getOffsetX();
	offsetRotations = bestMove.getOffsetRotations();
}

// A method that gets a vector of all the possible moves for the computer players 
// current piece, compares the moves and returns the best move in the vector
Move Computer::compareMoves(const vector<Move>& moves) const
{
	Move bestMove(0, 0, GameConfig::NUM_POINTS_IN_SHAPE, 0, 0);

	for (const Move& move : moves)
	{
		if (move.getNumFullRows() > bestMove.getNumFullRows())
			bestMove = move;

		else if (move.getNumFullRows() == bestMove.getNumFullRows() &&
				 move.getHighestPoint() > bestMove.getHighestPoint())
			bestMove = move;
		
		else if (move.getNumFullRows() == bestMove.getNumFullRows() &&
				 move.getHighestPoint() == bestMove.getHighestPoint() &&
			     move.getNumHighestPoints() < bestMove.getNumHighestPoints())
			bestMove = move;
	}

	return bestMove;
}

// A method that adds all the possible moves for the computer players current piece to the given moves vector
void Computer::addMoves(vector<Move>& moves, Board& currBoard, Shape& currPiece, size_t rotation) const
{
	Move currMove;
	bool canMoveLeft = true;

	while (canMoveLeft)
	{
		while (currPiece.moveAndDontDraw(GameConfig::eDirections::DOWN));

		if (currPiece.getPieceType() == GameConfig::ePieces::BOMB)
			currMove = Move(currBoard.countFullRows(), currBoard.getHighestPointY(),
							currBoard.getNumHighestPoints(), currPiece.getCenterX() - getSpawnX(), rotation);
		else
			currMove = Move(currBoard.countFullRows(), currPiece.getHighestPointY(),
							currPiece.getNumHighestPoints(), currPiece.getCenterX() - getSpawnX(), rotation);

		moves.push_back(currMove);
		currBoard = getCurrBoard();

		while (currPiece.moveAndDontDraw(GameConfig::eDirections::UP));

		canMoveLeft = currPiece.moveAndDontDraw(GameConfig::eDirections::LEFT);
	}
}

// A method that rotates the given piece clockwise and move it to the top right 
// corner of the board without printing the changes to the console screen
void Computer::rotateAndMoveToTopRight(Shape& currPiece) const
{
	currPiece.moveAndDontDraw(GameConfig::eDirections::RIGHT);
	currPiece.moveAndDontDraw(GameConfig::eDirections::DOWN);
	currPiece.rotateAndDontDraw(GameConfig::eRotations::CLOCKWISE);

	while (currPiece.moveAndDontDraw(GameConfig::eDirections::UP));
	while (currPiece.moveAndDontDraw(GameConfig::eDirections::RIGHT));
}

// A method that spawns a piece for a computer player
void Computer::spawnPiece()
{
	Player::spawnPiece();
	findBestMove();
}

// A method that rotates and moves the computer players current piece to its 
// destination according to the offsetX and offsetRotations data members values
void Computer::executeKbhit(GameConfig::eKeys keyPressed)
{
	if (!wait)
	{
		if (offsetRotations > 0)
		{
			if (rotateCurrPiece(GameConfig::eRotations::CLOCKWISE))
				--offsetRotations;
		}

		else
		{
			if (offsetX < 0)
			{
				moveCurrPiece(GameConfig::eDirections::LEFT);
				++offsetX;
			}

			else if (offsetX > 0)
			{
				moveCurrPiece(GameConfig::eDirections::RIGHT);
				--offsetX;
			}
		}
	}

	wait = !wait;
}

// A method that returns a random in a range according to the computer
// players level to indicate wither thee current move is a mistake
size_t Computer::getRandNum() const
{
	switch (level)
	{
	case GameConfig::eLevels::BEST:
		return -1;
	case GameConfig::eLevels::GOOD:
		return rand() % GameConfig::TURNS_FOR_ERROR_GOOD;
	case GameConfig::eLevels::NOVICE:
		return rand() % GameConfig::TURNS_FOR_ERROR_NOVICE;
	default:
		break;
	}
}
