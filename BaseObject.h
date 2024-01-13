#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "SDL.h"
#include <iostream>

class BaseObject
{
protected:
	SDL_Rect m_Rect;

public:
	BaseObject(SDL_Rect rect,
		float relW = 1,
		float relH = 1,
		float relX = 0.5f,
		float relY = 0.5f,
		bool orgAtCenter = true);

	inline SDL_Rect GetRect() const { return m_Rect; }
	bool MouseIsWithin(const int& x, const int& y) const;
};

#endif // !BASE_OBJECT_H_
