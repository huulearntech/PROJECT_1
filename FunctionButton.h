#pragma once

#ifndef FUNCTIONBUTTON_H_
#define FUNCTIONBUTTON_H_

#include "Button.h"
#include "Board.h"

class FunctionButton : public Button
{
public:
	FunctionButton(SDL_Rect rect, SDL_Color selectColor, SDL_Color hoverColor) : Button(rect, selectColor, hoverColor) {}

	void Draw();

	void HandleEvent(SDL_Event event, Board* board);

private:
	std::string m_TextureID = "un_hint";
};


#endif // !FUNCTIONBUTTON_H_
