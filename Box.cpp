#include "Box.h"
#include "TextureManager.h"

bool Box::SetNumber(int number)
{
	if (number < 0 || number > 9) {
		m_Number = 0;
		return false;
	}
	m_Number = number;
	return true;
}

void Box::Draw() const
{
	BaseObject::Draw();
	std::string textureID = "" + m_Number;
	TextureManager::GetInstance()->Draw(textureID, m_Rect);
}
