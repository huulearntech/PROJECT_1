#include "Label.h"
#include "TextureManager.h"

Label::Label(SDL_Rect rect,
	SDL_Texture* texture,
	float relW,
	float relH,
	float relX,
	float relY,
	bool orgAtCenter)
	: BaseObject(rect, relW, relH, relX, relY, orgAtCenter) {
	Label::m_Rect = BaseObject::m_Rect;
	Label::m_Texture = texture;
}

void Label::Draw() const
{
	TextureManager::GetInstance()->Draw(Label::m_Texture,Label:: m_Rect);
}

void Label::SetTexture(std::string textureID)
{
	Label::m_Texture = TextureManager::GetInstance()->GetTexture(textureID);
}
