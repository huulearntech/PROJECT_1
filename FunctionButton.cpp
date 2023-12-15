#include "FunctionButton.h"
#include "TextureManager.h"

void FunctionButton::Draw()
{
	Button::Draw();
	TextureManager::GetInstance()->Draw(m_TextureID, m_Rect);
}

void FunctionButton::HandleEvent(SDL_Event event, Board* board)
{
	if ((FunctionButton::MouseIsWithin(event.motion.x, event.motion.y) && event.type == SDL_MOUSEBUTTONDOWN) || event.type == SDL_MOUSEMOTION)
	{
		Button::HandleEvent(event);
		//if (m_Selected) m_TextureID = "act_hint";
		//else m_TextureID = "un_hint";

	}
	if (m_Selected && board->GetCurrentBox() != nullptr) {
		if (board->GetCurrentBox()->GetNumber() != board->GetCurrentBox()->GetCorrectNumber()) {
			board->GetCurrentBox()->SetNumber(board->GetCurrentBox()->GetCorrectNumber());
		}
	}
}
