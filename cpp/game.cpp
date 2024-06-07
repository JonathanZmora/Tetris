#include "game.h"
#include "general.h"

#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;

// A method to display the menu on the console screen
void Game::displayMenu() const
{
	clrscr();
	gotoxy(0, 0);

	cout << "Choose an option:" << endl;
	cout << "(1) Start a new game - Human vs Human" << endl;
	cout << "(2) Start a new game - Computer vs Computer" << endl;
	cout << "(3) Start a new game - Human vs Computer" << endl;

	if (isPaused)
		cout << "(4) Continue a paused game" << endl;

	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}

// A method to display the game instructions and keys on the console screen
void Game::displayInstructions() const
{
	clrscr(); // Clear the screen
	gotoxy(0, 0); // Take cursor to top left of the console

	cout << "Player 1 Keys (Left board):" << endl;
	cout << "a - move left" << endl;
	cout << "d - move right" << endl;
	cout << "s - rotate clockwise" << endl;
	cout << "w - rotate counter clockwise" << endl;
	cout << "x - drop" << endl;
	cout << "escape - pause game" << endl << endl;

	cout << "Player 2 Keys (Right board):" << endl;
	cout << "j - move left" << endl;
	cout << "l - move right" << endl;
	cout << "k - rotate clockwise" << endl;
	cout << "i - rotate counter clockwise" << endl;
	cout << "m - drop" << endl;
	cout << "escape - pause game" << endl << endl;

	cout << "Instructions:" << endl;
	cout << "Each players objective is to move and rotate the" << endl;
	cout << "falling pieces on the board to form full lines." << endl;
	cout << "When a full line is formed it disappears and all" << endl;
	cout << "The lines above it fall down. If a player cannot" << endl;
	cout << "make the blocks disappear quickly enough, the field" << endl;
	cout << "will start to fill. when the pieces reach the top of" << endl;
	cout << "the field, the game ends and the player loses." << endl;
	cout << "The B piece is a bomb that blows up a 9 point radius on the board." << endl << endl;

	cout << "Press any key to go back to the main menu";

	char keyPressed = _getch(); // Take the pressed key out of the buffer
}

// A method that runs the game until the user exits 
void Game::run()
{
	GameConfig::eMenuOptions chosenOption;
	bool exit = false;

	while (!exit) // run game until user exits
	{
		displayMenu(); // display menu

		chosenOption = (GameConfig::eMenuOptions)_getch(); // wait for user to choose an option

		switch (chosenOption)
		{
		case GameConfig::eMenuOptions::NEW_HVH_GAME:
			clrscr(); 
			newHvHGame();
			break;
		case GameConfig::eMenuOptions::NEW_CVC_GAME:
			clrscr();
			newCvCGame();
			break;
		case GameConfig::eMenuOptions::NEW_HVC_GAME:
			clrscr();
			newHvCGame();
			break;
		case GameConfig::eMenuOptions::RESUME_GAME:
			resumeGame();
			break;
		case GameConfig::eMenuOptions::INSTRUCTIONS:
			displayInstructions();
			break;
		case GameConfig::eMenuOptions::EXIT:
			exit = true;
			break;
		default:
			break;
		}
	}
}

// A method that starts a new human vs human game 
void Game::newHvHGame()
{
	setUpHvH();
	setUpNewGame();
	play();
}

// A method that starts a new computer vs computer game 
void Game::newCvCGame()
{
	setUpCvC();
	setUpNewGame();
	play();
}

// A method that starts a new human vs computer game 
void Game::newHvCGame()
{
	setUpHvC();
	setUpNewGame();
	play();
}

// A method that resumes a paused game
void Game::resumeGame()
{
	setUpPausedGame();
	play();
}

// A method that executes the game loop until the game is paused or a player lost
void Game::play()
{
	while (!isPaused) // if game is paused stop the loop
	{
		if (player1->moveDownAndCheckIfLost()) // try to move player 1's piece down
		{
			finishGame("2");
			break;
		}

		if (player2->moveDownAndCheckIfLost()) // try to move player 2's piece down
		{
			finishGame("1");
			break;
		}

		executeKbhits(); // handle the keys that were pressed by players
	}
}

// a method that prints who the winner of the game is to the console screen,
// and waits for any key to be pressed to return to the main menu
void Game::finishGame(const char* winner) const
{
	gotoxy(GameConfig::BOARD_ONE_X + GameConfig::GAME_WIDTH / 2, GameConfig::GAME_HEIGHT + GameConfig::BOARDS_Y + 1);
	cout << "THE WINNER IS: PLAYER " << winner << "!";
	gotoxy(GameConfig::BOARD_ONE_X + GameConfig::GAME_WIDTH / 2, GameConfig::GAME_HEIGHT + GameConfig::BOARDS_Y + 2);
	cout << "Press any key to continue";
	char keyPressed = _getch(); // Take the pressed key out of the buffer
}

// A method that handles the keys that are pressed by the players during gameplay
void Game::executeKbhits()
{
	GameConfig::eKeys keyPressed;

	for (size_t i = 0; i < 5; i++) { // handle 5 keys at a time and stop if the game is paused

		keyPressed = GameConfig::eKeys::NONE;

		if (_kbhit())
		{
			keyPressed = (GameConfig::eKeys)_getch();

			if (keyPressed == GameConfig::eKeys::ESCAPE) 
			{
				isPaused = true;
				break;
			}
		}

		player1->executeKbhit(keyPressed);
		player2->executeKbhit(keyPressed);
		
		Sleep(100);
	}
}

// A method that is called in the beginning of a new game to 
// set up the game object data members for a new game
void Game::setUpNewGame()
{
	isPaused = false;
	player1->spawnPiece();
	player2->spawnPiece();
	Sleep(400);
}

// A method that is called when a paused game is resumed to set the
//  console screen to the point where the last game was paused
void Game::setUpPausedGame()
{ 
	clrscr(); // clear the screen
	isPaused = false;
	player1->resumePausedGame();
	player2->resumePausedGame();
}

// A method that gets a computer players level from the user and returns it
GameConfig::eLevels Game::getLevel(size_t playerNum) const
{
	gotoxy(0, 0);
	cout << "Choose player " << playerNum << " level:" << endl;
	cout << "(1) BEST" << endl << "(2) GOOD" << endl << "(3) NOVICE";
	GameConfig::eLevels level = (GameConfig::eLevels)_getch();
	clrscr();
	return level;
}

// A method that is called in the beginning of a new computer vs computer
// game to set up the game object data members accordingly for a new game
void Game::setUpCvC()
{
	GameConfig::eLevels player1Level = getLevel(1);
	GameConfig::eLevels player2Level = getLevel(2);
	deletePlayers();
	player1 = new Computer({ GameConfig::BOARD_ONE_X, GameConfig::BOARDS_Y }, GameConfig::PLAYER_ONE_KEYS, player1Level);
	player2 = new Computer({ GameConfig::BOARD_TWO_X, GameConfig::BOARDS_Y }, GameConfig::PLAYER_TWO_KEYS, player2Level);
}

// A method that is called in the beginning of a new human vs computer
// game to set up the game object data members accordingly for a new game
void Game::setUpHvC()
{
	GameConfig::eLevels player2Level = getLevel(2);
	deletePlayers();
	player1 = new Human({ GameConfig::BOARD_ONE_X, GameConfig::BOARDS_Y }, GameConfig::PLAYER_ONE_KEYS);
	player2 = new Computer({ GameConfig::BOARD_TWO_X, GameConfig::BOARDS_Y }, GameConfig::PLAYER_TWO_KEYS, player2Level);
}

// A method that is called in the beginning of a new human vs human
// game to set up the game object data members accordingly for a new game
void Game::setUpHvH()
{
	deletePlayers();
	player1 = new Human({ GameConfig::BOARD_ONE_X, GameConfig::BOARDS_Y }, GameConfig::PLAYER_ONE_KEYS);
	player2 = new Human({ GameConfig::BOARD_TWO_X, GameConfig::BOARDS_Y }, GameConfig::PLAYER_TWO_KEYS);
}

// A method that frees the memory allocated for the player objects
void Game::deletePlayers()
{
	if (!player1) delete player1;
	if (!player2) delete player2;
}
