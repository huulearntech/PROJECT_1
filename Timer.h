#pragma once

#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include "BaseObject.h"

class Timer
{
public:
	Timer() {
		m_CurrentTime = m_StartTime = SDL_GetTicks();
		m_ElapsedTime = 0;
	}

	void ShowTime() {
		m_CurrentTime = SDL_GetTicks();
		if ((m_CurrentTime - m_StartTime) / 1000 != m_ElapsedTime) {
			m_ElapsedTime = (m_CurrentTime - m_StartTime) / 1000;
			std::cout << m_ElapsedTime << '\n';
		}
	}

private:
	Uint32 m_StartTime;
	Uint32 m_CurrentTime;
	Uint32 m_ElapsedTime;
};

#endif // !TIMER_H_
