#pragma once
#ifndef ERASERBUTTON_H_
#define ERASERBUTTON_H_

#include "Button.h"
#include "Texture.h"
#include "TextureManager.h"

class EraserButton : public Button
{
private:
	Texture* m_Texture;
public:
	EraserButton(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor)
		: Button(rect, normalColor, selectColor, hoverColor)
	{
		m_Texture = new Texture(rect, TextureManager::GetInstance()->GetTexture("eraser"));
	}

	void Draw() {
		Button::Draw();
		m_Texture->Draw();
	}
};


#endif // !ERASERBUTTON_H_
