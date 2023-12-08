#include "Button.h"

Button::Button()
{
	m_State = ButtonState::MOUSE_OUT;
	m_Texture = nullptr;
	m_ButtonRect = { 0,0,0,0 };
	m_TextureRect = { 0,0,0,0 };
	m_MouseOutColor = { 219, 184, 215, SDL_ALPHA_OPAQUE };
	m_MouseHoveringColor = { 95, 89, 191, SDL_ALPHA_OPAQUE };
	m_MouseDownColor = { 91, 191, 116, SDL_ALPHA_OPAQUE };
	m_MouseUpColor = { 95, 89, 191, SDL_ALPHA_OPAQUE };
	m_Selected = false;
}

void Button::SetTexture(SDL_Texture* texture)
{
	m_Texture = texture;
}

//void Button::SetButtonRect(const SDL_Rect& rect)
//{
//	m_ButtonRect = rect;
//}

//void Button::SetTextureRect(const SDL_Rect& rect)
//{
//	m_TextureRect = rect;
//}
//
//void Button::CenterTextureRect()
//{
//	int textureWidth, textureHeight;
//	SDL_QueryTexture(m_Texture, NULL, NULL, &textureWidth, &textureHeight);
//	const int textureStartRow = m_ButtonRect.y + 0.5 * (m_ButtonRect.h - textureHeight);
//	const int textureStartCol = m_ButtonRect.x + 0.5 * (m_ButtonRect.w - textureWidth);
//	m_TextureRect = { textureStartCol, textureStartRow, textureWidth, textureHeight };
//}

void Button::SetSelected(const bool selected)
{
	m_Selected = selected;
}

bool Button::MouseIsWithin(const int& x, const int& y) const
{
	return m_ButtonRect.x > x
		&& m_ButtonRect.x < x + m_ButtonRect.w
		&& m_ButtonRect.y > y
		&& m_ButtonRect.y < y + m_ButtonRect.h;
}

// These lines of code are darn good :))
ButtonState Button::GetMouseEvent(const SDL_Event* event)
{
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (!MouseIsWithin(x, y)) {
			m_State = ButtonState::MOUSE_OUT;
		}
		else {
			switch (event->type) {
				case SDL_MOUSEMOTION:
					m_State = ButtonState::MOUSE_HOVERING;
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_State = ButtonState::MOUSE_DOWN;
					break;
				case SDL_MOUSEBUTTONUP:
					m_State = ButtonState::MOUSE_UP;
					break;
				default:
					break;
			}
		}
	}
	return m_State;
}

void Button::SetMouseDownColor(const SDL_Color& color)
{
	m_MouseDownColor = color;
}

void Button::RenderButton(SDL_Renderer* renderer)
{
	if (m_Selected) {
		SDL_SetRenderDrawColor(renderer, m_MouseDownColor.r, m_MouseDownColor.g, m_MouseDownColor.b, m_MouseDownColor.a);
	}
	else {
		switch (m_State)
		{
		case ButtonState::MOUSE_OUT:
			SDL_SetRenderDrawColor(renderer, m_MouseOutColor.r, m_MouseOutColor.g, m_MouseOutColor.b, m_MouseOutColor.a);
			break;
		case ButtonState::MOUSE_HOVERING:
			SDL_SetRenderDrawColor(renderer, m_MouseHoveringColor.r, m_MouseHoveringColor.g, m_MouseHoveringColor.b, m_MouseHoveringColor.a);
			break;
		case ButtonState::MOUSE_DOWN:
		SDL_SetRenderDrawColor(renderer, m_MouseDownColor.r, m_MouseDownColor.g, m_MouseDownColor.b, m_MouseDownColor.a);
			break;
		case ButtonState::MOUSE_UP:
			SDL_SetRenderDrawColor(renderer, m_MouseUpColor.r, m_MouseUpColor.g, m_MouseUpColor.b, m_MouseUpColor.a);
			break;
		default:
			break;
		}
	}
}

void Button::RenderTexture(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_Texture, nullptr, &m_TextureRect);
}
