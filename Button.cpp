#include "Button.h"
#include "TextureManager.h"

void Button::HandleEvent(SDL_Event event)
{
	if (MouseIsWithin(event.motion.x, event.motion.y))
	{
		switch (event.type) 
		{
			case SDL_MOUSEBUTTONDOWN:
				m_Selected = !m_Selected;
				break;
			case SDL_MOUSEMOTION:
				if (!m_Hovered)
				{
					m_Hovered = true;
				}
				break;
			default:
				break;
		}
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
		if (m_Hovered) m_Hovered = false;
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
