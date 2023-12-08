#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "SDL.h"

enum class ButtonState
{
	MOUSE_OUT = 0,
	MOUSE_HOVERING = 1,
	MOUSE_DOWN = 2,
	MOUSE_UP = 3
};

constexpr SDL_Color MOUSE_OUT_COLOR = { 255, 255, 255, 255 };
constexpr SDL_Color MOUSE_HOVERING_COLOR = { 255, 255, 255, 255 };
constexpr SDL_Color MOUSE_DOWN_COLOR = { 255, 255, 255, 255 };

class Button
{
public:
	Button();
	void SetTexture(SDL_Texture* texture);

	//void SetButtonRect(const SDL_Rect& rect);

	//void SetTextureRect(const SDL_Rect& rect);

	//void CenterTextureRect();

	void SetSelected(const bool selected);

	bool MouseIsWithin(const int& x, const int& y) const;

	ButtonState GetMouseEvent(const SDL_Event* event);

	void SetMouseDownColor(const SDL_Color& color);

	void RenderButton(SDL_Renderer* renderer);

	void RenderTexture(SDL_Renderer* renderer);

private:
	ButtonState m_State;
	SDL_Texture* m_Texture;
	SDL_Rect m_ButtonRect;
	SDL_Rect m_TextureRect;

	bool m_Selected;

protected:
	SDL_Color m_MouseOutColor;
	SDL_Color m_MouseHoveringColor;
	SDL_Color m_MouseDownColor;
	SDL_Color m_MouseUpColor;
};

#endif // !BUTTON_H_
