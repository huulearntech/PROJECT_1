#include "BaseObject.h"

BaseObject::BaseObject(SDL_Rect rect,
	float relW,
	float relH,
	float relX,
	float relY,
	bool orgAtCenter)
{
	float x = rect.x + rect.w * relX;
	float y = rect.y + rect.h * relY;
	float w = rect.w * relW;
	float h = rect.h * relH;

	if (orgAtCenter) {
		x -= w / 2;
		y -= h / 2;
	}
	m_Rect = { (int)x, (int)y, (int)w, (int)h };
}

bool BaseObject::MouseIsWithin(const int& x, const int& y) const
{
	if (x < m_Rect.x) return false;
	if (x > m_Rect.x + m_Rect.w) return false;
	if (y < m_Rect.y) return false;
	if (y > m_Rect.y + m_Rect.h) return false;
	
	return true;
}

