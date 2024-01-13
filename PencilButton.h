#pragma once

#ifndef PENCILBUTTON_H_
#define PENCILBUTTON_H_

#include "Button.h"
#include "Texture.h"
#include "TextureManager.h"

class PencilButton : public Button
{
public:
	PencilButton(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor)
		:Button(rect, normalColor, selectColor, hoverColor)
	{
		m_PencilIcon = new Texture(rect, TextureManager::GetInstance()->GetTexture("pencil_off"));
	}

	void Update() {
		Button::Update();
		if (m_Selected) m_PencilIcon->SetTexture("pencil_on");
		else m_PencilIcon->SetTexture("pencil_off");
	}

	void Draw() {
		Button::Draw();
		m_PencilIcon->Draw();
	}

private:
	Texture* m_PencilIcon;
};

#endif // !PENCILBUTTON_H_
