#include "human.h"

// A method that handles a key that was pressed by a human player
void Human::executeKbhit(GameConfig::eKeys keyPressed)
{
	if (isKeyRelevant(keyPressed))
	{
		switch (keyPressed)
		{
		case GameConfig::eKeys::LEFT_ONE:
			moveCurrPiece(GameConfig::eDirections::LEFT);
			break;
		case GameConfig::eKeys::RIGHT_ONE:
			moveCurrPiece(GameConfig::eDirections::RIGHT);
			break;
		case GameConfig::eKeys::ROTATE_CLOCKWISE_ONE:
			rotateCurrPiece(GameConfig::eRotations::CLOCKWISE);
			break;
		case GameConfig::eKeys::ROTATE_COUNTER_ONE:
			rotateCurrPiece(GameConfig::eRotations::COUNTER_CLOCKWISE);
			break;
		case GameConfig::eKeys::DROP_ONE:
			dropCurrPiece();
			break;
		case GameConfig::eKeys::LEFT_TWO:
			moveCurrPiece(GameConfig::eDirections::LEFT);
			break;
		case GameConfig::eKeys::RIGHT_TWO:
			moveCurrPiece(GameConfig::eDirections::RIGHT);
			break;
		case GameConfig::eKeys::ROTATE_CLOCKWISE_TWO:
			rotateCurrPiece(GameConfig::eRotations::CLOCKWISE);
			break;
		case GameConfig::eKeys::ROTATE_COUNTER_TWO:
			rotateCurrPiece(GameConfig::eRotations::COUNTER_CLOCKWISE);
			break;
		case GameConfig::eKeys::DROP_TWO:
			dropCurrPiece();
			break;
		default:
			break;
		}
	}
}
