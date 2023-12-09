#include "BaseObject.h"

bool BaseObject::MouseIsWithin(const int& x, const int& y) const
{
	if (x < m_Rect.x) return false;
	if (x > m_Rect.x + m_Rect.w) return false;
	if (y < m_Rect.y) return false;
	if (y > m_Rect.y + m_Rect.h) return false;
	
	return true;
}

