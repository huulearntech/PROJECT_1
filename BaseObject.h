#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "SDL.h"

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

	bool MouseIsWithin(const int& x, const int& y) const;
};

#endif // !BASE_OBJECT_H_
