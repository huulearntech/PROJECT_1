#pragma once

#ifndef HINTBUTTON_H_
#define HINTBUTTON_H_

#include "Button.h"
#include "Board.h"
#include <string>

class HintButton : public Button
{
public:
	HintButton(SDL_Rect rect, SDL_Color selectColor, SDL_Color hoverColor) : Button(rect, selectColor, hoverColor) {}

	void Draw();

	void HandleEvent(SDL_Event& event, Board* board);

private:
	std::string m_TextureID = "hint_3";
	int m_HintAvailable = 3;
};


#endif // !HINTBUTTON_H_
