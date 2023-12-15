#pragma once
#ifndef BOX_H_
#define BOX_H_

#include "Button.h"


class Box : public Button
{
private:
	int m_Number;
	int m_CorrectNumber;
	bool m_IsConst;
	bool m_Draft[10] = { false };

public:
	Box(SDL_Rect rect, SDL_Color selectColor, SDL_Color hoverColor, int number, int correctNumber) : Button(rect, selectColor, hoverColor)
	{
		m_Number = number;
		m_CorrectNumber = correctNumber;
		m_IsConst = (number == correctNumber && number != 0);
	}

	~Box() {}

	bool IsCorrect() const { return m_Number == m_CorrectNumber; }
	bool SetNumber(int number);
	inline int GetNumber() const { return m_Number; }
	inline int GetCorrectNumber() const { return m_CorrectNumber; }
	int HandleEvent(SDL_Event event);
	void Draw();
};

#endif // !BOX_H_
