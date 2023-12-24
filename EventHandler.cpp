#include "EventHandler.h"
#include "Game.h"
#include "Button.h"


EventHandler* EventHandler::s_Instance = nullptr;

void EventHandler::Listen()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
				Game::GetInstance()->Close();
				break;
			case SDL_MOUSEBUTTONDOWN:
				EventHandler::HandleEvent(event,
					Game::GetInstance()->m_Board,
					Game::GetInstance()->m_ControlsWrapper,
					Game::GetInstance()->m_Numpad);
				Game::GetInstance()->m_Timer->HandleMouseDown(event);
				break;
			case SDL_MOUSEMOTION:
				Game::GetInstance()->m_Board->HandleMouseMotion(event);
				Game::GetInstance()->m_Numpad->HandleMouseMotion(event);
				Game::GetInstance()->m_ControlsWrapper->HandleMouseMotion(event);
				Game::GetInstance()->m_Timer->HandleMouseMotion(event);
				break;
			default:
				break;
		}
	}
}

void EventHandler::HandleEvent(SDL_Event& event, Board* board, GameControlsWrapper* controlsWrapper, Numpad* numpad)
{
	Game::GetInstance()->m_Board->HandleMouseDown(event);
	Game::GetInstance()->m_Numpad->HandleMouseDown(event);
	Game::GetInstance()->m_ControlsWrapper->HandleMouseDown(event);
}

void EventHandler::Update(Board* board, GameControlsWrapper* controlsWrapper, Numpad* numpad)
{
	if (board->GetCurrentCell() == nullptr) return;
	Uint8 mode = controlsWrapper->GetState();

	if (mode & GameMode::ERASER) {
		board->GetCurrentCell()->SetNumber(0);
		board->GetCurrentCell()->SetDraftNumber(0);
	}
	if (mode & GameMode::HINT) {
		if (controlsWrapper->GetHintButton()->HintAvailable()) {
			bool hintSuccess = board->GetCurrentCell()->ShowHint();
			if (hintSuccess) {
				controlsWrapper->GetHintButton()->DecreaseHint();
			}
		}
	}
	if (mode & GameMode::PENCIL) {
		board->GetCurrentCell()->SetDraftNumber(numpad->GetNumber());
	}
	if (!mode) {
		board->GetCurrentCell()->SetNumber(numpad->GetNumber());
	}
}
