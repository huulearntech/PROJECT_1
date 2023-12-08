#pragma once
#ifndef BOARD_H_
#define BOARD_H_

#include "Box.h"
#include <vector>

constexpr int BOARD_SIZE = 9;

enum class LEVEL
{
	EASY,
	MEDIUM,
	HARD,
	EXTREME
};

constexpr int NUMBER_OF_RECORDS = 100;

// 81 = 9*9 square per record, x2 for mask
constexpr int RECORD_SIZE = 2 * BOARD_SIZE * BOARD_SIZE;

const std::string EASY_FILE_PATH = "easy_database.txt";
const std::string MEDIUM_FILE_PATH = "medium_database.txt";
const std::string HARD_FILE_PATH = "hard_database.txt";
const std::string EXTREME_FILE_PATH = "extreme_database.txt";

constexpr int BOARD_SIZE_IN_PX = 600;
constexpr int BORDER_SIZE_IN_PX = BOARD_SIZE_IN_PX / 100;
constexpr int BOX_SIZE_IN_PX = (9 * BOARD_SIZE_IN_PX) / 100;
constexpr SDL_Color BOARD_BKG = { 52, 72, 97, 255 }; //BLUE GRAY

class Board : public BaseObject
{
private:
	Box* m_Board[BOARD_SIZE][BOARD_SIZE] = { nullptr };

public:	
	bool Init(LEVEL level);
	bool LoadData(LEVEL level);
	void Draw();
	void Update(const int& mouseX, const int& mouseY) const;
};


#endif // !BOARD_H_
