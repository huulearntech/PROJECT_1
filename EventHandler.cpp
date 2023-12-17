#include "EventHandler.h"
#include "Game.h"
#include "Button.h"


EventHandler* EventHandler::s_Instance = nullptr;

EventHandler::EventHandler() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
	m_KeyClicked = false;
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
			default:
				break;
		}
	}
}

int EventHandler::HandleKeyboard(SDL_Event& event)
{
	SDL_Keycode keycode = event.key.keysym.sym;
	if (keycode >= SDLK_1 && keycode <= SDLK_9) { return (int)(keycode - SDLK_0); }
	else if (keycode == SDLK_DELETE || keycode == SDLK_BACKSPACE) { return 0; }
	return -1;
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

