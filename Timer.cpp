#include "Timer.h"
#include "TextureManager.h"
#include "Game.h"

Timer::Timer(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor)
	: Button(rect, normalColor, selectColor, hoverColor)
{
	m_StartTime = SDL_GetTicks();
	m_ElapsedTime = 0;
	m_Texture = nullptr;
}

void Timer::Update() {
	Uint32 now = SDL_GetTicks();
	if (m_Selected) {
		//m_TextureID = "timer_off";
		m_StartTime = now - m_ElapsedTime;
	}
	else {
		//m_TextureID = "timer_on";
		Uint32 elapsed_time = now - m_StartTime;
		if (elapsed_time / 1000 != m_ElapsedTime / 1000) IncreaseTime();
		m_ElapsedTime = elapsed_time;
	}
}

void Timer::Draw()
{
	Button::Draw();
	TextureManager::GetInstance()->Draw(m_Texture, m_Rect);
	if (m_Selected) {
		SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 50, 90, 175, 255);
		SDL_RenderDrawRect(Game::GetInstance()->GetRenderer(), &m_Rect);
	}
}

void Timer::IncreaseTime()
{
	SDL_DestroyTexture(m_Texture);

	// Convert from milisecond to second
	int seconds = (m_ElapsedTime / 1000) % 60;
	int minutes = m_ElapsedTime / 60000;
	std::string now = std::to_string(minutes / 10)
		+ std::to_string(minutes % 10)
		+ ":"
		+ std::to_string(seconds / 10)
		+ std::to_string(seconds % 10);

	m_Texture = TextureManager::GetInstance()->CreateTextureFromString(now, Color::black);
}
