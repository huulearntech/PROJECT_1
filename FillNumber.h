#pragma once

#ifndef FILLNUMBER_H_
#define FILLNUMBER_H_

#include "Button.h"
#include "Texture.h"

class FillNumber : public Button
{
private:
	int m_Number;
	int m_Remain;
	Texture* m_NumberLabel;
	Texture* m_RemainLabel;
public:
	FillNumber(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor, int number, int remain);

	inline void SetRemain(int remain) { m_Remain = remain; }
	inline bool IsActivated() const { return m_Remain > 0; }
	void Draw();
	void Update();
};


#endif // !FILLNUMBER_H_
