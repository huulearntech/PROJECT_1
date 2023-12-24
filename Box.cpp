#include "Box.h"
#include "TextureManager.h"

Box::Box(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor, int number, int correctNumber)
	: Button(rect, normalColor, selectColor, hoverColor)
{
	m_HoldingNumber = number;
	m_CorrectNumber = correctNumber;
	m_IsGiven = (number == correctNumber && number != 0);
	m_NumberLabel = new Label(rect, nullptr, 0.4f, 0.8f);
	
	if (m_IsGiven) { m_NumberLabel->SetTexture("const_" + std::to_string(number)); }

	int draftBoxSize = rect.w / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			SDL_Texture* texture = TextureManager::GetInstance()->GetTexture("pencil_" + std::to_string(i * 3 + j + 1));
			m_DraftLabel[i * 3 + j] = new Label(rect, texture, 0.15f, 0.3f, (2 * j + 1) / 6.0f, (2 * i + 1) / 6.0f);
		}
	}
}

void Box::SetNumber(int number)
{
	if (!m_IsGiven && 0 <= number && number <= 9) { 
		m_HoldingNumber = number;
	}
}

void Box::SetDraftNumber(int number)
{
	if (number == 0) { memset(m_Draft, false, sizeof(m_Draft)); }
	else if (1 <= number && number <= 9) { m_Draft[number - 1] = !m_Draft[number - 1]; }
}

bool Box::ShowHint()
{
	if (m_HoldingNumber != m_CorrectNumber) {
		m_HoldingNumber = m_CorrectNumber;
		return true;
	}
	return false;
}

void Box::Update()
{
	Button::Update();
	if (!m_IsGiven) {
		if (m_HoldingNumber == 0) m_NumberLabel->SetTexture(nullptr);
		else {
			if (IsCorrect()) m_NumberLabel->SetTexture("correct_" + std::to_string(m_HoldingNumber));
			else {
				m_NumberLabel->SetTexture("wrong_" + std::to_string(m_HoldingNumber));
				m_CurrentColor = Color::pink;
			}
		}
	}
}

void Box::Draw()
{
	Button::Draw();
	if (m_HoldingNumber == 0) {
		for(int i = 0; i < 9; i++){
			if (m_Draft[i]) m_DraftLabel[i]->Draw();
		}
	}
	else {
		m_NumberLabel->Draw();
	}
}

Uint16 Box::Encode() const
{
	Uint16 code = 0;
	if (m_IsGiven) code = 100;
	else code = m_HoldingNumber;
	code += m_CorrectNumber;
	for (int i = 0; i < 9; i++) {
		code = (code << 1) | m_Draft[i];
	}
	return code;
}

void Box::Decode(Uint16 code)
{
	for (int i = 8; i >= 0; i--) {
		m_Draft[i] = code & 1;
		code >>= 1;
	}
	m_CorrectNumber = code % 10;
	m_HoldingNumber = code / 10;
	if (m_HoldingNumber == 10) {
		m_HoldingNumber = m_CorrectNumber;
		m_IsGiven = true;
	}
	else {
		m_IsGiven = false;
	}
}
