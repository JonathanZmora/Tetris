#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

// A class that stores constants and enums
class GameConfig
{
public:

	enum class eLevels {BEST = '1', GOOD = '2', NOVICE = '3' };
	enum class eMenuOptions { NEW_HVH_GAME = '1', NEW_CVC_GAME = '2', NEW_HVC_GAME = '3',
							  RESUME_GAME = '4', INSTRUCTIONS = '8', EXIT = '9' };
	enum class eDirections { LEFT, RIGHT, DOWN, UP };
	enum class eRotations { CLOCKWISE, COUNTER_CLOCKWISE };
	enum class ePieces { I_SHAPE, T_SHAPE, Z_SHAPE, L_SHAPE, J_SHAPE, S_SHAPE, B_SHAPE, BOMB, NONE };
	enum class eKeys { 
		LEFT_ONE = 'a', RIGHT_ONE = 'd', ROTATE_CLOCKWISE_ONE = 's', ROTATE_COUNTER_ONE = 'w', DROP_ONE = 'x',
		LEFT_TWO = 'j', RIGHT_TWO = 'l', ROTATE_CLOCKWISE_TWO = 'k', ROTATE_COUNTER_TWO = 'i', DROP_TWO = 'm',
		ESCAPE = 27, NONE = 0
	};

	static constexpr eKeys PLAYER_ONE_KEYS[] = {
		eKeys::LEFT_ONE, eKeys::RIGHT_ONE, eKeys::DROP_ONE,
		eKeys::ROTATE_CLOCKWISE_ONE, eKeys::ROTATE_COUNTER_ONE,
	};

	static constexpr eKeys PLAYER_TWO_KEYS[] = {
		eKeys::LEFT_TWO, eKeys::RIGHT_TWO, eKeys::DROP_TWO,
		eKeys::ROTATE_CLOCKWISE_TWO, eKeys::ROTATE_COUNTER_TWO,
	};

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int BOARD_ONE_X = 23;
	static constexpr int BOARD_TWO_X = 45;
	static constexpr int BOARDS_Y = 2;
	static constexpr int NUM_PIECE_TYPES = 8;
	static constexpr int NUM_ROTATIONS = 4;
	static constexpr int NUM_POINTS_IN_SHAPE = 4;
	static constexpr int NUM_KEYS = 5;
	static constexpr int TURNS_FOR_ERROR_GOOD = 40;
	static constexpr int TURNS_FOR_ERROR_NOVICE = 10;
	static constexpr int BOARD_ONE_SPAWN_X = GAME_WIDTH / 2 + BOARD_ONE_X - 1;
	static constexpr int BOARD_TWO_SPAWN_X = GAME_WIDTH / 2 + BOARD_TWO_X - 1;
	static constexpr char BORDER_CHAR = '*';
	static constexpr char PIECE_CHAR = '#';
	static constexpr char BOMB_CHAR = 'B';
	static constexpr char WHITE_SPACE = ' ';

};

#endif 

