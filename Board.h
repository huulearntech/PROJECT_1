#pragma once
#ifndef BOARD_H_
#define BOARD_H_

#include "Box.h"

constexpr int UNDEFINED = -1;
constexpr int BOARD_SIZE = 9;

namespace Level
{
	const std::string easy = "Easy";
	const std::string medium = "Medium";
	const std::string hard = "Hard";
	const std::string extreme = "Extreme";
};

constexpr int NUMBER_OF_RECORDS = 100;

// 163 = 9*9 square per record, x2 for mask + 1 for end of line
// I don't know how it works :)) why this should add 2 to RECORD_SIZE, but it just works
constexpr int RECORD_SIZE = 2 * BOARD_SIZE * BOARD_SIZE + 2;

constexpr int BOARD_SIZE_IN_PX = 554;
constexpr int BOX_SIZE_IN_PX = 60;

const int BoxesCoordinates[] = { 2, 63, 124, 186, 247, 308, 370, 431, 492 };

class Board : public BaseObject
{
private:
	Box* m_Board[BOARD_SIZE][BOARD_SIZE] = { nullptr };
	int m_CurrRow;
	int m_CurrCol;

	int m_MistakeCount;

	bool m_IsHidden;
	bool m_MakeMistake;
	std::string m_TextureID;

	int m_State;

public:	
	Board(SDL_Rect rect) : BaseObject(rect)	{
		m_CurrRow = m_CurrCol = UNDEFINED; 
		m_MistakeCount = 0;
		m_IsHidden = false;
		m_TextureID = "board";
		m_MakeMistake = false;

		m_State = 999999999;
	}
	//bool Init(std::string level);
	bool LoadData(std::string filepath);
	void HandleMouseDown(SDL_Event& event);
	void HandleMouseMotion(SDL_Event& event);
	Box* GetCurrentCell() const
	{
		if (m_CurrRow != UNDEFINED && m_CurrCol != UNDEFINED) { return m_Board[m_CurrRow][m_CurrCol]; }
		return nullptr;
	}

	void SetNumber(int number);
	inline int GetMistakeCount() const { return m_MistakeCount; }
	inline bool MakeMistake() const { return m_MakeMistake; }
	inline void SetHidden(bool hidden) { m_IsHidden = hidden; }
	inline bool IsHidden() const { return m_IsHidden; }

	void Highlight();
	void Update();
	void Draw();
	void Reset();

	inline int GetState() const { return m_State; }
};

#endif // !BOARD_H_
