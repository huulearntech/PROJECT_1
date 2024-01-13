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
				if (Game::GetInstance()->m_ChooseLevelPage->IsActivate()) {
					Game::GetInstance()->m_ChooseLevelPage->HandleMouseDown(event);
				} else
				EventHandler::HandleEvent(event,
					Game::GetInstance()->m_BoardWrapper,
					Game::GetInstance()->m_ControlsWrapper,
					Game::GetInstance()->m_Numpad);
				break;
			case SDL_MOUSEBUTTONUP:
				Game::GetInstance()->m_ControlsWrapper->HandleMouseUp();
				Game::GetInstance()->m_Numpad->HandleMouseUp();
				break;
			case SDL_MOUSEMOTION:
				if (Game::GetInstance()->m_ChooseLevelPage->IsActivate()) {
					Game::GetInstance()->m_ChooseLevelPage->HandleMouseMotion(event);
				}
				else
				Game::GetInstance()->m_BoardWrapper->HandleMouseMotion(event);
				Game::GetInstance()->m_Numpad->HandleMouseMotion(event);
				Game::GetInstance()->m_ControlsWrapper->HandleMouseMotion(event);
				break;
			default:
				break;
		}
	}
}

void EventHandler::HandleEvent(SDL_Event& event, BoardWrapper* boardWrapper, GameControlsWrapper* controlsWrapper, Numpad* numpad)
{
	boardWrapper->HandleMouseDown(event);
	controlsWrapper->HandleMouseDown(event);
	numpad->HandleMouseDown(event);
}

void EventHandler::Update(BoardWrapper* boardWrapper, GameControlsWrapper* controlsWrapper, Numpad* numpad)
{
	if (boardWrapper->GetBoard()->GetCurrentCell() == nullptr) return;
	Uint8 mode = controlsWrapper->GetState();

	if (mode & GameMode::ERASER) {
		boardWrapper->GetBoard()->GetCurrentCell()->SetNumber(0);
		boardWrapper->GetBoard()->GetCurrentCell()->SetDraftNumber(0);
	}
	if (mode & GameMode::HINT) {
		if (controlsWrapper->GetHintButton()->HintAvailable()) {
			bool hintSuccess = boardWrapper->GetBoard()->GetCurrentCell()->ShowHint();
			if (hintSuccess) {
				controlsWrapper->GetHintButton()->DecreaseHint();
			}
		}
	}
	if (mode & GameMode::PENCIL) {
		boardWrapper->GetBoard()->GetCurrentCell()->SetDraftNumber(numpad->GetNumber());
	}
	if (!mode) {
		boardWrapper->GetBoard()->SetNumber(numpad->GetNumber());
	}

	numpad->SetRemainNumbers(boardWrapper->GetBoard()->GetState());
}
