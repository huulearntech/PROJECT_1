#include "Button.h"
#include "TextureManager.h"

void Button::HandleEvent(SDL_Event& event)
{
	if (m_Hovered != MouseIsWithin(event.motion.x, event.motion.y)) m_Hovered = !m_Hovered;
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (m_Hovered) m_Selected = !m_Selected;
		else m_Selected = false;
	}
	Update();
}

void Button::Update()
{
	if (m_Selected) m_CurrentColor = m_SelectColor;
	else if (m_Hovered) m_CurrentColor = m_HoverColor;
	else m_CurrentColor = MOUSE_OUT_COLOR;
}

void Button::Draw()
{
	TextureManager::GetInstance()->Draw(m_CurrentColor, Button::m_Rect);
}
