#include "Box.h"
#include "TextureManager.h"

bool Box::SetNumber(int number)
{
	if (m_IsConst) return false;
	if (number < 0 || number > 9) {
		m_Number = 0;
		return false;
	}
	m_Number = number;
	return true;
}

int Box::HandleEvent(SDL_Event event)
{
	Button::HandleEvent(event);
	if (m_Selected) return m_Number;
	return -1;
}

void Box::Draw()
{
	Button::Draw();

	if (m_Number == 0) {
		for (int i = 1; i <= 9; i++) {
			 // draw draft
		}
	}
	else {
		std::string textureID = std::to_string(m_Number);
		if (m_IsConst) textureID = "const_" + textureID;
		else if (IsCorrect()) textureID = "correct_" + textureID;
		else textureID = "wrong_" + textureID;
		TextureManager::GetInstance()->Draw(textureID, m_Rect);
	}
}
