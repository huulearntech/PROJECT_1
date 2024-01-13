#include "HintButton.h"
#include "TextureManager.h"
#include "Game.h"

void HintButton::Draw() const
{
	Button::Draw();
	TextureManager::GetInstance()->Draw(m_TextureID, m_Rect);
}

void HintButton::Update()
{
	Button::Update();
	m_TextureID = "hint_" + std::to_string(m_HintAvailable);
}
