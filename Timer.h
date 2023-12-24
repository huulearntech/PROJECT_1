#pragma once

#ifndef TIMER_H_
#define TIMER_H_

#include "Button.h"

class Timer : public Button
{
public:
	Timer(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor);

	void Draw();

	void Update();


	inline Uint32 GetTime() const { return m_ElapsedTime; }
	
	void IncreaseTime();

	inline void Reset() {
		m_StartTime = SDL_GetTicks();
		m_ElapsedTime = 0;
	}


private:
	Uint32 m_StartTime;
	Uint32 m_ElapsedTime;

	SDL_Texture* m_Texture;
};

#endif // !TIMER_H_
