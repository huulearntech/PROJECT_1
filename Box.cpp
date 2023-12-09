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

void Box::Draw()
{
	Button::Draw();
	std::string textureID = std::to_string(m_Number);
	if (m_IsConst) textureID = "const_" + textureID;
	else if (IsCorrect()) textureID = "correct_" + textureID;
	else textureID = "wrong_" + textureID;
	TextureManager::GetInstance()->Draw(textureID, m_Rect);
}
