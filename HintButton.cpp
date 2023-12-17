#include "HintButton.h"
#include "TextureManager.h"
#include "Game.h"

void HintButton::Draw()
{
	Button::Draw();
	TextureManager::GetInstance()->Draw(m_TextureID, m_Rect);
}
void HintButton::HandleEvent(SDL_Event& event, Board* board)
{
	Button::HandleEvent(event);
	if (event.type == SDL_MOUSEBUTTONUP && MouseIsWithin(event.motion.x, event.motion.y)) {
		m_Selected = false;
		Update();
	}
	if (m_Selected && board->GetCurrentCell() != nullptr) {
		if (m_HintAvailable > 0) {
			if (board->GetCurrentCell()->GetHoldingNumber() != board->GetCurrentCell()->GetCorrectNumber()) {
				board->GetCurrentCell()->SetNumber(board->GetCurrentCell()->GetCorrectNumber());
				m_HintAvailable--;
				m_TextureID = "hint_" + std::to_string(m_HintAvailable);
			}
		}
		else {
			m_TextureID = "hint_0";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, nullptr, "Out of hint!", Game::GetInstance()->GetWindow());
			m_Selected = false;
		}
	}
}
