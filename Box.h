#pragma once
#ifndef BOX_H_
#define BOX_H_

#include "Button.h"

class Box : public Button
{
private:
	int m_HoldingNumber;
	int m_CorrectNumber;
	bool m_IsGiven;
	bool m_Draft[10] = { false };

public:
	Box(SDL_Rect rect, SDL_Color selectColor, SDL_Color hoverColor, int number, int correctNumber) : Button(rect, selectColor, hoverColor)
	{
		m_HoldingNumber = number;
		m_CorrectNumber = correctNumber;
		m_IsGiven = (number == correctNumber && number != 0);
	}

	~Box() {}

	bool IsCorrect() const { return m_HoldingNumber == m_CorrectNumber; }
	bool SetNumber(int number);
	bool SetDraftNumber(int number);
	inline int GetHoldingNumber() const { return m_HoldingNumber; }
	inline int GetCorrectNumber() const { return m_CorrectNumber; }

	int HandleEvent(SDL_Event& event);
	void Draw();
};

#endif // !BOX_H_
