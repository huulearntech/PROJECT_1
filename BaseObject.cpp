#include "BaseObject.h"
#include "TextureManager.h"

bool BaseObject::MouseIsWithin(const int& x, const int& y) const
{
	return x > m_Rect.x
		&& x < m_Rect.x + m_Rect.w
		&& y > m_Rect.y
		&& y < m_Rect.y + m_Rect.h;
}

void BaseObject::Draw() const
{
	TextureManager::GetInstance()->Draw(m_TextureID, m_Rect);
}
