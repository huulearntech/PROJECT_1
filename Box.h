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

public:
	Box(SDL_Rect rect, int number, int correctNumber) : Button(rect) {
		m_Number = number;
		m_CorrectNumber = correctNumber;
		m_IsConst = (number == correctNumber && number != 0);
	}

	bool IsCorrect() const { return m_Number == m_CorrectNumber; }
	bool SetNumber(int number);
	void Draw();
};

#endif // !BOX_H_
