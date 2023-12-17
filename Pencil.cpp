#include "Pencil.h"
#include "TextureManager.h"

void Pencil::Draw()
{
	if (m_Selected) m_TextureID = "pencil_on";
	else m_TextureID = "pencil_off";
	Button::Draw();
	TextureManager::GetInstance()->Draw(m_TextureID, m_Rect);
}

void Pencil::HandleEvent(SDL_Event& event)
{
	if (MouseIsWithin(event.motion.x, event.motion.y) || event.type == SDL_MOUSEMOTION) Button::HandleEvent(event);
	return;
}
