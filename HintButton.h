#pragma once

#ifndef HINTBUTTON_H_
#define HINTBUTTON_H_

#include "Button.h"
#include <string>

class HintButton : public Button
{
public:
	HintButton(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor)
		: Button(rect, normalColor, selectColor, hoverColor) {}

	void Draw() const;

	inline void DecreaseHint() { m_HintAvailable = (m_HintAvailable > 0 ? m_HintAvailable - 1 : 0); }
	inline bool HintAvailable() const { return m_HintAvailable > 0; }
	void Update();

private:
	int m_HintAvailable = 3;
	std::string m_TextureID;
};


#endif // !HINTBUTTON_H_
