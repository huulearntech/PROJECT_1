#pragma once
#ifndef BOARD_H_
#define BOARD_H_

#include "Box.h"

constexpr int BOARD_SIZE = 9;

enum class LEVEL
{
	EASY,
	MEDIUM,
	HARD,
	EXTREME
};

constexpr int NUMBER_OF_RECORDS = 100;

// 163 = 9*9 square per record, x2 for mask + 1 for end of line
// I don't know how it works :)) why this should add 2 to RECORD_SIZE, but it just works
constexpr int RECORD_SIZE = 2 * BOARD_SIZE * BOARD_SIZE + 2;

constexpr int BOARD_SIZE_IN_PX = 550;
constexpr int BORDER_SIZE_IN_PX = 1;
constexpr int BOX_SIZE_IN_PX = 60;
constexpr SDL_Color BOARD_BKG = { 52, 72, 97, 255 }; //BLUE GRAY

class Board : public BaseObject
{
private:
	Box* m_Board[BOARD_SIZE][BOARD_SIZE] = { nullptr };
	Box* m_CurrentBox;

public:	
	Board(SDL_Rect rect) : BaseObject(rect)
	{
		this->m_Rect = rect;
		m_CurrentBox = nullptr;
	}
	bool Init(LEVEL level);
	bool LoadData(LEVEL level);
	void Draw() override;
	void HandleEvent(SDL_Event event);
	inline Box* GetCurrentBox() const { return m_CurrentBox; }


	~Board() {
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				m_Board[i][j]->~Box();
			}

		}
	}
};


#endif // !BOARD_H_
