#ifndef __HUMAN_H
#define __HUMAN_H

#include "player.h"

// A class to represent a human player 
class Human : public Player
{
public:
	Human(const Point& boardTopLeft, const GameConfig::eKeys _keys[]) :
		Player(boardTopLeft, _keys) {};
	Human() {};

	void executeKbhit(GameConfig::eKeys keyPressed) override;
};

#endif 
