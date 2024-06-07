#ifndef __GAME_H
#define __GAME_H

#include "board.h"
#include "shape.h"
#include "player.h"
#include "human.h"
#include "computer.h"

// A class that is responsible for the gameplay
class Game
{
	bool isPaused = false;
	Player* player1 = nullptr;
	Player* player2 = nullptr;

public:
	Game() {}
	~Game() { deletePlayers(); };
	void run();

private:
	void play();
	void resumeGame();
	void displayMenu() const;
	void displayInstructions() const;
	void finishGame(const char* winner) const;
	void executeKbhits();
	void setUpNewGame();
	void setUpPausedGame();
	void setUpCvC();
	void setUpHvH();
	void setUpHvC();
	void newCvCGame();
	void newHvHGame();
	void newHvCGame();
	void deletePlayers();
	GameConfig::eLevels getLevel(size_t playerNum) const;
};

#endif 
