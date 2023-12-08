#include "EventHandler.h"
#include "Game.h"
#include "TextureManager.h"


EventHandler* EventHandler::s_Instance = nullptr;

EventHandler::EventHandler() {
	m_Mouse = new Mouse();
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}


void EventHandler::Listen()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
				Game::GetInstance()->Close();
				break;
			case SDL_KEYDOWN:
				KeyDown();
				break;
			case SDL_MOUSEMOTION:
				MouseTrack();
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					LeftMouseClicked();
				}
				break;
			default:
				break;
		}
	}
}

void EventHandler::MouseTrack()
{
	SDL_GetMouseState(&(m_Mouse->X), &(m_Mouse->Y));
	printf("X: %d, Y: %d\n", m_Mouse->X, m_Mouse->Y);
}

void EventHandler::LeftMouseClicked()
{
	printf("Left Mouse Clicked\n");

}

void EventHandler::LeftMouseClicked(Box* dest, Box* src)
{
}

bool EventHandler::GetKeyDown(SDL_Scancode key)
{
	if (m_KeyStates[key] == 1) {
		return true;
	}
	return false;
}

bool EventHandler::CursorIsWithin(BaseObject* object)
{
	return EventHandler::GetInstance()->GetMouse()->X > object->GetRect().x
		&& EventHandler::GetInstance()->GetMouse()->X < object->GetRect().x + object->GetRect().w
		&& EventHandler::GetInstance()->GetMouse()->Y > object->GetRect().y
		&& EventHandler::GetInstance()->GetMouse()->Y < object->GetRect().y + object->GetRect().h;
}

void EventHandler::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

