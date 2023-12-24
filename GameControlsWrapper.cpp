#include "GameControlsWrapper.h"

GameControlsWrapper::GameControlsWrapper(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor)
	: BaseObject(rect) {
	SDL_Rect pencilRect = { rect.x, rect.y, rect.h, rect.h };
	SDL_Rect eraserRect = { rect.x + 70, rect.y, rect.h, rect.h };
	SDL_Rect hintRect = { rect.x + 140, rect.y, rect.h, rect.h };
	m_Pencil = new Button(pencilRect, normalColor, selectColor, hoverColor);
	m_Eraser = new Button(eraserRect, normalColor, selectColor, hoverColor);
	m_Hint = new HintButton(hintRect, normalColor, selectColor, hoverColor);
	m_State = 0;
}

void GameControlsWrapper::HandleMouseDown(SDL_Event& event)
{
	if (m_Pencil->MouseIsWithin(event.motion.x, event.motion.y)) {
		m_Pencil->HandleMouseDown(event);
	}
	m_Eraser->HandleMouseDown(event);
	m_Hint->HandleMouseDown(event);
	m_State = 0;
	if (m_Pencil->IsSelected()) m_State |= GameMode::PENCIL;
	if (m_Eraser->IsSelected()) m_State |= GameMode::ERASER;
	if (m_Hint->IsSelected()) m_State |= GameMode::HINT;
}

void GameControlsWrapper::HandleMouseMotion(SDL_Event& event)
{
	m_Pencil->HandleMouseMotion(event);
	m_Eraser->HandleMouseMotion(event);
	m_Hint->HandleMouseMotion(event);
}

void GameControlsWrapper::Draw()
{
	m_Pencil->Draw();
	m_Eraser->Draw();
	m_Hint->Draw();
}

void GameControlsWrapper::Update()
{
	m_Pencil->Update();
	m_Eraser->SetSelect(false);
	m_Eraser->Update();
	m_Hint->Update();
}
