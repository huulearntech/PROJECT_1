#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "BaseObject.h"
#include <string>

class Texture : public BaseObject
{
private:
	SDL_Rect m_Rect;
	SDL_Texture* m_Texture;

public:
	Texture(SDL_Rect rect,
		SDL_Texture* texture,
		float relW = 1,
		float relH = 1,
		float relX = 0.5f,
		float relY = 0.5f,
		bool orgAtCenter = true);
	
	void Draw() const;
	void SetTexture(SDL_Texture* texture) { m_Texture = texture; }
	void SetTexture(std::string textureID);
	void DestroyTexture();

	~Texture() { DestroyTexture(); }
};

#endif // !TEXTURE_H_
