#include "Box.h"
#include "TextureManager.h"

bool Box::SetNumber(int number)
{
	if (0 <= number && number <= 9) { 
		m_HoldingNumber = number;
		if(number > 0) return IsCorrect();
	}
	return true;
}

bool Box::SetDraftNumber(int number)
{
	if(m_HoldingNumber != 0) return false;
	if (number == 0) {
		memset(m_Draft, false, sizeof(m_Draft));
	}
	else m_Draft[number] = !m_Draft[number];
	return true;
}

int Box::HandleEvent(SDL_Event& event)
{
	Button::HandleEvent(event);
	if (m_Selected) return m_HoldingNumber;
	return -1;
}

void Box::Draw()
{
	Button::Draw();
	std::string textureID;
	if (m_HoldingNumber == 0) {
		int draftSize = m_Rect.w / 3;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (m_Draft[i*3+j+1]) {
					textureID = "pencil_" + std::to_string(i * 3 + j + 1);
					TextureManager::GetInstance()->Draw(textureID, { m_Rect.x + draftSize * j, m_Rect.y + draftSize * i, draftSize, draftSize });
				}
			}
		}
	}
	else {
		textureID = std::to_string(m_HoldingNumber);
		if (m_IsGiven) textureID = "const_" + textureID;
		else if (IsCorrect()) textureID = "correct_" + textureID;
		else textureID = "wrong_" + textureID;
		TextureManager::GetInstance()->Draw(textureID, m_Rect);
	}
}
