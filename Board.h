#pragma once
#ifndef BOARD_H_
#define BOARD_H_

#include "Box.h"
#include "Pencil.h"

constexpr int UNDEFINED = -1;
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

constexpr int BOARD_SIZE_IN_PX = 554;
constexpr int THIN_BORDER_SIZE_IN_PX = 1;
constexpr int BOX_SIZE_IN_PX = 60;
constexpr SDL_Color BOARD_BKG = { 52, 72, 97, 255 }; //BLUE GRAY

const int BoardAssets[] = { 2, 63, 124, 186, 247, 308, 370, 431, 492 };

class Board : public BaseObject
{
private:
	Box* m_Board[BOARD_SIZE][BOARD_SIZE] = { nullptr };
	int m_CurrRow;
	int m_CurrCol;

	int m_WrongTimesLeft;

public:	
	Board(SDL_Rect rect) : BaseObject(rect)	{
		m_CurrRow = m_CurrCol = UNDEFINED; 
		m_WrongTimesLeft = 3;
	}
	bool Init(LEVEL level);
	void Draw() override;
	void HandleEvent(SDL_Event& event);
	void HandleKeyboard(SDL_Event& event, Pencil* pencil);
	Box* GetCurrentCell() const
	{
		if (m_CurrRow != -1 && m_CurrCol != -1) { return m_Board[m_CurrRow][m_CurrCol]; }
		return nullptr;
	}

	int GetCurrCol() { return m_CurrCol; }
	int GetCurrRow() { return m_CurrRow; }

	void SuggestRelatedCells();
	bool IsCompleted();
	bool GameOver() const { return m_WrongTimesLeft <= 0; }


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
