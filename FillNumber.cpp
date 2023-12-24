#include "FillNumber.h"
#include "TextureManager.h"

FillNumber::FillNumber(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor, int number, int remain)
	: Button(rect, normalColor, selectColor, hoverColor)
{
	FillNumber::m_Number = number;
	FillNumber::m_Remain = remain;
	FillNumber::m_NumberLabel = new Label(rect, nullptr, 0.4f, 0.8f);
	FillNumber::m_RemainLabel = new Label(rect, nullptr, 0.2f, 0.4f, 0.7f, 0, false);
}

void FillNumber::Draw()
{
	Button::Draw();
	FillNumber::m_NumberLabel->Draw();
	FillNumber::m_RemainLabel->Draw();
}

void FillNumber::Update()
{
	m_Selected = false;
	Button::Update();
	//set label;
	FillNumber::m_NumberLabel->SetTexture(TextureManager::GetInstance()->GetTexture("correct_" + std::to_string(m_Number)));
	FillNumber::m_RemainLabel->SetTexture(TextureManager::GetInstance()->GetTexture("pencil_" + std::to_string(m_Remain)));
}
