#pragma once

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "SDL.h"
#include "Board.h"
#include "Pencil.h"

class EventHandler
{
public:
	static EventHandler* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new EventHandler();
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	void KeyDown();
	int HandleKeyboard(SDL_Event& event);
	bool m_KeyClicked;

private:
	EventHandler();
	const Uint8* m_KeyStates;
	static EventHandler* s_Instance;


};
#endif // !EVENTHANDLER_H_
