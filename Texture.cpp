#include "Texture.h"
#include "TextureManager.h"

Texture::Texture(SDL_Rect rect,
	SDL_Texture* texture,
	float relW,
	float relH,
	float relX,
	float relY,
	bool orgAtCenter)
	: BaseObject(rect, relW, relH, relX, relY, orgAtCenter) {
	Texture::m_Rect = BaseObject::m_Rect;
	Texture::m_Texture = texture;
}

void Texture::Draw() const
{
	TextureManager::GetInstance()->Draw(Texture::m_Texture,Texture:: m_Rect);
}

void Texture::SetTexture(std::string textureID)
{
	Texture::m_Texture = TextureManager::GetInstance()->GetTexture(textureID);
}

void Texture::DestroyTexture()
{
	SDL_DestroyTexture(m_Texture);
	m_Texture = nullptr;
}

