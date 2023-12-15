#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "SDL.h"

class BaseObject
{
protected:
	SDL_Rect m_Rect;

public:
	BaseObject(SDL_Rect rect) {
		m_Rect = rect;
	}

	inline void SetRect(SDL_Rect rect) { m_Rect = rect; }
	inline SDL_Rect GetRect() const { return m_Rect; }
	bool MouseIsWithin(const int& x, const int& y) const;
	
	virtual void Draw() = 0;
};

#endif // !BASE_OBJECT_H_
