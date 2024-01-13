#pragma once
#ifndef CHOOSELEVELPAGE_H_
#define CHOOSELEVELPAGE_H_

#include "AbstractPage.h"
#include "Button.h"
#include "Texture.h"
#include "TextureManager.h"

class ChooseLevelPage : public AbstractPage
{
private:
	Button* m_Buttons[4] = { nullptr };
	Texture* m_LevelTextures[4] = { nullptr };

public:
	ChooseLevelPage(SDL_Rect rect) {
		m_IsActivate = true;

		for (int i = 0; i < 4; i++) {
			m_Buttons[i] = new Button({ rect.x, rect.y + i * rect.h / 4, rect.w, rect.h / 5 }, Color::cyan, Color::light_cyan, Color::light_cyan);
		}
		m_LevelTextures[0] = new Texture(m_Buttons[0]->GetRect(),
			TextureManager::GetInstance()->CreateTextureFromString("Easy", Color::gray_blue),
			0.25f,
			0.7f);
		m_LevelTextures[1] = new Texture(m_Buttons[1]->GetRect(),
			TextureManager::GetInstance()->CreateTextureFromString("Medium", Color::gray_blue),
			0.4f,
			0.7f);
		m_LevelTextures[2] = new Texture(m_Buttons[2]->GetRect(),
			TextureManager::GetInstance()->CreateTextureFromString("Hard", Color::gray_blue),
			0.25f,
			0.7f);
		m_LevelTextures[3] = new Texture(m_Buttons[3]->GetRect(),
			TextureManager::GetInstance()->CreateTextureFromString("Extreme", Color::gray_blue),
			0.4f,
			0.7f);
	}

	// Inherited via AbstractPage
	void Draw() override;
	void Update() override;
	void HandleMouseDown(SDL_Event& event);
	void HandleMouseMotion(SDL_Event& event);
};

#endif // !CHOOSELEVELPAGE_H_
