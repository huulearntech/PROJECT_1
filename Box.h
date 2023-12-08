#pragma once
#ifndef BOX_H_
#define BOX_H_

#include "BaseObject.h"


class Box : public BaseObject
{
private:
	int m_Number;
	int m_CorrectNumber;
	bool m_IsClicked;

public:
	Box(std::string textureID, SDL_Rect rect, int number, int correctNumber) : BaseObject(textureID, rect) {
		m_Number = number;
		m_CorrectNumber = correctNumber;
		m_IsClicked = false;
	}

	bool IsCorrect() const { return m_Number == m_CorrectNumber; }
	bool SetNumber(int number);
	void SetClicked(bool isClicked) { m_IsClicked = isClicked; }
	bool IsClicked() const { return m_IsClicked; }
	void Draw() const;
};

#endif // !BOX_H_
