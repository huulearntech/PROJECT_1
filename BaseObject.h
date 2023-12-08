#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include <string>
#include "SDL.h"

class BaseObject
{
protected:
	std::string m_TextureID;
	SDL_Rect m_Rect;

public:
	BaseObject(std::string textureID, SDL_Rect rect) {
		m_TextureID = textureID;
		m_Rect = rect;
	}

	void SetRect(const int& x, const int& y) { m_Rect.x = x; m_Rect.y = y; }
	SDL_Rect GetRect() const { return m_Rect; }
	bool MouseIsWithin(const int& x, const int& y) const;
	void Draw() const;
};

#endif // !BASE_OBJECT_H_
