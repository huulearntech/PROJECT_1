#include "Pencil.h"
#include "TextureManager.h"

void Pencil::Draw()
{
	Button::Draw();
	TextureManager::GetInstance()->Draw(m_TextureID, m_Rect);
}

void Pencil::HandleEvent(SDL_Event event, Board* board)
{
	Button::HandleEvent(event);
	if (m_Selected && board->GetCurrentBox() != nullptr) {

	}
}
