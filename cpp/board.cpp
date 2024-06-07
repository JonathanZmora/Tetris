#include "board.h"
#include "general.h"

#include <iostream>
using namespace std;

// Constructor
Board::Board(const Point& _topLeft) : topLeft(_topLeft) 
{
	for (int row = 0; row < GameConfig::GAME_HEIGHT; row++)
		for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
			board[row][col] = GameConfig::WHITE_SPACE;
}

// A method that draws the borders for the calling board object
void Board::drawBorders() const
{
	int topLeftX = this->topLeft.getX(), topLeftY = this->topLeft.getY();

	for (int col = topLeftX - 1; col <= topLeftX + GameConfig::GAME_WIDTH; col++)
	{
		gotoxy(col, topLeftY - 1);
		cout << GameConfig::BORDER_CHAR;

		gotoxy(col, topLeftY + GameConfig::GAME_HEIGHT);
		cout << GameConfig::BORDER_CHAR;
	}

	for (int row = topLeftY - 1; row <= topLeftY + GameConfig::GAME_HEIGHT; row++)
	{
		gotoxy(topLeftX - 1, row);
		cout << GameConfig::BORDER_CHAR;

		gotoxy(topLeftX + GameConfig::GAME_WIDTH, row);
		cout << GameConfig::BORDER_CHAR;
	}
}

// A method the gets the coordinates of a point and returns
// true if the point is within the board, and false otherwise
bool Board::isPointInBounds(int x, int y) const
{
	if (topLeft.getX() <= x && x < topLeft.getX() + GameConfig::GAME_WIDTH)
		if (topLeft.getY() <= y && y < topLeft.getY() + GameConfig::GAME_HEIGHT)
			return true;
	return false;
}

// A method that gets an array of points and fills the corresponding cells in the 
// board array with the character # as a representation of a piece on the board
void Board::fillPoints(vector<Point> points, char ch)
{
	for (const Point& p : points)
		board[p.getY() - topLeft.getY()][p.getX() - topLeft.getX()] = ch;
}

// A method that eliminates full rows from the board 
void Board::dropFullRows()
{
	bool isRowFull;;
	Board updatedBoard(topLeft);
	int rowIndex = GameConfig::GAME_HEIGHT - 1;

	for (int row = GameConfig::GAME_HEIGHT - 1; row >= 0; row--)
	{
		isRowFull = true;

		for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
		{
			if (board[row][col] == GameConfig::WHITE_SPACE)
			{
				isRowFull = false;
				break;
			}
		}

		if (!isRowFull) {
			for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
				updatedBoard.board[rowIndex][col] = board[row][col];
			rowIndex--;
		}
	}

	*this = Board(updatedBoard);
	drawBoard();
}

// A method that returns the number of full rows in the board.
size_t Board::countFullRows() const
{
	size_t counter = 0;

	for (int row = 0; row < GameConfig::GAME_HEIGHT; ++row)
	{
		bool isRowFull = true;

		for (int col = 0; col < GameConfig::GAME_WIDTH; ++col)
		{
			if (board[row][col] == GameConfig::WHITE_SPACE)
			{
				isRowFull = false;
				break;
			}
		}

		if (isRowFull)
			++counter;
	}

	return counter;
}

// A method that draws the boards content
void Board::drawBoard() const
{
	for (int row = 0; row < GameConfig::GAME_HEIGHT; row++) {
		for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
			gotoxy(topLeft.getX() + col, topLeft.getY() + row);
			cout << board[row][col];
		}
	}
}

// A method that returns true if the top row in the board is empty, and false otherwise
bool Board::isFirstRowEmpty() const
{
	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
		if (board[0][col] != GameConfig::WHITE_SPACE)
			return false;
	return true;
}

// A method that drops all the points in the board that are between leftBound and rightBound 
// and above lowerBound down until they hit the bottom of the board or a full point
void Board::dropPoints(size_t lowerBound, size_t leftBound, size_t rightBound)
{
	int tempRow;

	for (int row = lowerBound; row >= 0; --row)
	{
		for (int col = leftBound; col <= rightBound; ++col)
		{
			if (board[row][col] == GameConfig::PIECE_CHAR)
			{
				board[row][col] = GameConfig::WHITE_SPACE;

				tempRow = row;
				while (board[tempRow][col] != GameConfig::PIECE_CHAR && tempRow < GameConfig::GAME_HEIGHT)
					++tempRow;

				board[tempRow - 1][col] = GameConfig::PIECE_CHAR;
			}
		}
	}
}

// A method that returns the highest row index in the board that is not empty
int Board::getHighestPointY() const
{
	for (size_t row = 0; row < GameConfig::GAME_HEIGHT; ++row)
		for (size_t col = 0; col < GameConfig::GAME_WIDTH; ++col)
			if (board[row][col] == GameConfig::PIECE_CHAR)
				return row;

	return GameConfig::GAME_HEIGHT;
}

// A method that returns the number of points int the heighest row that is not empty 
int Board::getNumHighestPoints() const
{
	int highestRow = getHighestPointY(), counter = 0;

	for (size_t col = 0; col < GameConfig::GAME_WIDTH; ++col)
		if (board[highestRow][col] == GameConfig::PIECE_CHAR)
			++counter;

	return counter;
}
