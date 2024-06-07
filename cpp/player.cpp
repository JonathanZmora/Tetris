#include "player.h"
#include <iostream>

// Constructor
Player::Player(const Point& boardTopLeft, const GameConfig::eKeys _keys[])
{
	board = boardTopLeft;
	spawnLocation = { boardTopLeft.getX() + GameConfig::GAME_WIDTH / 2, boardTopLeft.getY() };
	
	for (size_t i = 0; i < GameConfig::NUM_KEYS; i++)
		keys[i] = _keys[i];
	
	board.drawBorders();
}

// A method that spawns a new piece on the players board
void Player::spawnPiece()
{
	GameConfig::ePieces pieceType = GameConfig::ePieces(rand() % GameConfig::NUM_PIECE_TYPES);
	currPiece = Shape(spawnLocation, &board, pieceType);
	currPiece.draw();
}

// A method that prepares a paused game player object to be resumed
void Player::resumePausedGame() const
{
	board.drawBorders();
	board.drawBoard();
	currPiece.draw();
}

// A method that returns true if the key that was pressed is relevant to the player
bool Player::isKeyRelevant(GameConfig::eKeys keyPressed) const
{
	for (GameConfig::eKeys key : keys)
		if (key == keyPressed)
			return true;
	return false;
}

// A method that moves the players current piece down. if the piece cannot move down,
// the method checks if the player lost the game and if not it drops the players full rows
// and spawns a new piece. The method returns true if the player lost, false otherwise.
bool Player::moveDownAndCheckIfLost()
{
	if (!currPiece.move(GameConfig::eDirections::DOWN)) 
	{
		if (!board.isFirstRowEmpty()) 
			return true;

		board.dropFullRows();
		spawnPiece(); 
	}

	return false;
}
