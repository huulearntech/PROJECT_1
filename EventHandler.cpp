#include "EventHandler.h"
#include "Game.h"
#include "Button.h"


EventHandler* EventHandler::s_Instance = nullptr;

EventHandler::EventHandler() {
	m_Mouse = new Mouse();
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}


void EventHandler::Listen()
{
	//SDL_Event event;
	while (SDL_PollEvent(&m_Event)) {
		switch (m_Event.type)
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
				if (m_Event.button.button == SDL_BUTTON_LEFT) {
					LeftMouseDown();
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

void EventHandler::LeftMouseDown()
{
	printf("Left Mouse Clicked\n");

}

bool EventHandler::GetKeyDown(SDL_Scancode key)
{
	if (m_KeyStates[key] == 1) {
		return true;
	}
	return false;
}


void EventHandler::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

