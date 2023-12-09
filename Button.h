#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "SDL.h"
#include "BaseObject.h"

constexpr SDL_Color MOUSE_OUT_COLOR = { 255, 255, 255, 255 }; // WHITE
constexpr SDL_Color MOUSE_HOVERING_COLOR = { 226, 235, 243, 255 }; // SUPER LIGHT BLUE
constexpr SDL_Color MOUSE_DOWN_COLOR = { 187, 222, 251, 255 }; //LIGHT BLUE

class Button : public BaseObject
{
public:
	Button(SDL_Rect rect) : BaseObject(rect)
	{
		m_Selected = false;
		m_Hovered = false;
	}

	inline void SetSelected(const bool& selected) { m_Selected = selected; }
	inline void SetHovered(const bool& hovered) { m_Hovered = hovered; }

	void HandleEvent(SDL_Event event);

	void Draw() override;

protected:
	bool m_Selected;
	bool m_Hovered;
};

#endif // !BUTTON_H_
