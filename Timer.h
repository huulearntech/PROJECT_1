#pragma once

#ifndef TIMER_H_
#define TIMER_H_

#include "Button.h"
#include "Texture.h"

class Timer : public Button
{
public:
	Timer(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor);

	void Draw();

	void Update();

	void HandleMouseDown(SDL_Event& event) {
		if (MouseIsWithin(event.motion.x, event.motion.y)) {
			Button::HandleMouseDown(event);
		}
	}

	inline Uint32 GetTime() const { return m_ElapsedTime; }
	
	void IncreaseTime();

	inline void Reset() {
		m_StartTime = SDL_GetTicks();
		m_ElapsedTime = 0;
	}


private:
	Uint32 m_StartTime;
	Uint32 m_ElapsedTime;

	Texture* m_Clock;
	Texture* m_PauseIcon;
};

#endif // !TIMER_H_
