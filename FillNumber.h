#pragma once

#ifndef FILLNUMBER_H_
#define FILLNUMBER_H_

#include "Button.h"
#include "Label.h"

class FillNumber : public Button
{
private:
	int m_Number;
	int m_Remain;
	Label* m_NumberLabel;
	Label* m_RemainLabel;
public:
	FillNumber(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor, int number, int remain);

	inline void SetRemain(int remain) { m_Remain = remain; }
	inline bool IsActivate() const { return m_Remain > 0; }
	void Draw();
	void Update();
};


#endif // !FILLNUMBER_H_
