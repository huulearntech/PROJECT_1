#include "Button.h"
#include "TextureManager.h"

void Button::HandleEvent(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (MouseIsWithin(event.motion.x, event.motion.y)) { m_Selected = !m_Selected; }
		else { m_Selected = false; }
		//break;
	case SDL_MOUSEMOTION:
		if (m_Hovered != MouseIsWithin(event.motion.x, event.motion.y))
			m_Hovered = !m_Hovered;
		break;
	default:
		break;
	}
}

void Button::Draw()
{
	if (m_Selected) {
		TextureManager::GetInstance()->Draw(MOUSE_DOWN_COLOR, Button::m_Rect);
	}
	else if (m_Hovered)
	{
		TextureManager::GetInstance()->Draw(MOUSE_HOVERING_COLOR, Button::m_Rect);
	}
	else
	{
		TextureManager::GetInstance()->Draw(MOUSE_OUT_COLOR, Button::m_Rect);
	}
}
