#pragma once

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "SDL.h"
#include "Box.h"

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
	bool CursorIsWithin(BaseObject* object);
	void Hovering(Box* box);

private:
	EventHandler();

	Mouse* m_Mouse;

	void MouseTrack();
	void KeyDown();
	void LeftMouseClicked();
	void LeftMouseClicked(Box* dest, Box* src);

	const Uint8* m_KeyStates;
	static EventHandler* s_Instance;


};
#endif // !EVENTHANDLER_H_
