#pragma once

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "SDL.h"
#include "BoardWrapper.h"
#include "GameControlsWrapper.h"
#include "Numpad.h"

class EventHandler
{
public:
	static EventHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new EventHandler(); }

	void Listen();

	void HandleEvent(SDL_Event& event, BoardWrapper* boardWrapper, GameControlsWrapper* controlsWrapper, Numpad* numpad);
	void Update(BoardWrapper* boardWrapper, GameControlsWrapper* controlsWrapper, Numpad* numpad);

private:
	EventHandler() {}
	static EventHandler* s_Instance;


};
#endif // !EVENTHANDLER_H_
