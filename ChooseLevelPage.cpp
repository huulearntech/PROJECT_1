#include "ChooseLevelPage.h"

void ChooseLevelPage::Draw()
{
	TextureManager::GetInstance()->Draw("logo", { 500, 100, 200, 200 });
	TextureManager::GetInstance()->Draw("choose_level", { 500, 325, 200, 30 });

	for (int i = 0; i < 4; i++) {
		m_Buttons[i]->Draw();
		m_LevelTextures[i]->Draw();
	}
}

void ChooseLevelPage::Update()
{
	for (int i = 0; i < 4; i++) {
		m_Buttons[i]->Update();
		if (m_Buttons[i]->IsSelected()) {
			// Load Level


			m_IsActivate = false;
		}
	}
}

void ChooseLevelPage::HandleMouseDown(SDL_Event& event)
{
	for (int i = 0; i < 4; i++) {
		m_Buttons[i]->HandleMouseDown(event);
	}
}

void ChooseLevelPage::HandleMouseMotion(SDL_Event& event)
{
	for (int i = 0; i < 4; i++) {
		m_Buttons[i]->HandleMouseMotion(event);
	}
}
