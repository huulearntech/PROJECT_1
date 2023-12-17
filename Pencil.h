#pragma once

#ifndef PENCIL_H_
#define PENCIL_H_

#include "Button.h"
#include <string>


class Pencil : public Button
{
public:
	Pencil(SDL_Rect rect, SDL_Color selectColor, SDL_Color hoverColor) : Button(rect, selectColor, hoverColor) {}
	void Draw();

	void HandleEvent(SDL_Event& event);

private:
	std::string m_TextureID = "pencil_off";
};

#endif // !PENCIL_H_
