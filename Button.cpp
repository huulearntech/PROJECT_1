#include "Button.h"
#include "TextureManager.h"

Button::Button(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor)
	: BaseObject(rect)
{
	m_Selected = false;
	m_Hovered = false;
	m_PrevState = false;
	m_CurrentColor = m_NormalColor = normalColor;
	m_SelectColor = selectColor;
	m_HoverColor = hoverColor;
}

void Button::HandleMouseDown(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && MouseIsWithin(event.motion.x, event.motion.y)) m_Selected = !m_Selected;
	else m_Selected = false;
}

void Button::HandleMouseMotion(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION && m_Hovered != MouseIsWithin(event.motion.x, event.motion.y)) m_Hovered = !m_Hovered;
}

void Button::Update()
{
	m_PrevState = m_Selected;
	if (m_Selected) m_CurrentColor = m_SelectColor;
	else if (m_Hovered) m_CurrentColor = m_HoverColor;
	else m_CurrentColor = m_NormalColor;
}

void Button::Draw() const
{
	TextureManager::GetInstance()->Draw(m_CurrentColor, m_Rect);
}
