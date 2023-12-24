#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "BaseObject.h"
#include <string>

class Button : public BaseObject
{
public:
	Button(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor);

	inline void SetSelect(const bool& selected) { m_Selected = selected; }
	inline void SetColor(SDL_Color color) { m_CurrentColor = color; }
	inline bool IsSelected() const { return m_Selected; }
	inline bool OnClick() const { return !m_PrevState && m_Selected; }

	void HandleMouseDown(SDL_Event& event);
	void HandleMouseMotion(SDL_Event& event);

	void Update();
	void Draw() const;

protected:
	bool m_Selected;
	bool m_PrevState;
	bool m_Hovered;
	SDL_Color m_NormalColor;
	SDL_Color m_SelectColor;
	SDL_Color m_HoverColor;
	SDL_Color m_CurrentColor;
};

#endif // !BUTTON_H_
