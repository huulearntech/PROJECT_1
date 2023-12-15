#pragma once

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "SDL.h"

struct Mouse
{
public:
	int X, Y;

	Mouse(int x = 0, int y = 0) : X(x), Y(y) {}
};

class EventHandler
{
public:
	static EventHandler* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new EventHandler();
	}

	void Listen();
	Mouse* GetMouse() { return m_Mouse; }
	bool GetKeyDown(SDL_Scancode key);
	SDL_Event m_Event;

	void KeyDown();
	void MouseTrack();

private:
	EventHandler();

	Mouse* m_Mouse;


	void LeftMouseDown();

	const Uint8* m_KeyStates;
	static EventHandler* s_Instance;


};
#endif // !EVENTHANDLER_H_
