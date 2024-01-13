#include "Timer.h"
#include "TextureManager.h"
#include "Game.h"

Timer::Timer(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor)
	: Button(rect, normalColor, selectColor, hoverColor)
{
	m_StartTime = SDL_GetTicks();
	m_ElapsedTime = 0;
	m_Clock = new Texture(rect,
		TextureManager::GetInstance()->CreateTextureFromString("00:00", Color::pencil_gray),
		0.6f,
		1,
		0,
		0.1f,
		false);
	m_PauseIcon = new Texture(rect,
		TextureManager::GetInstance()->GetTexture("timer_pause"),
		0.3f,
		1,
		0.7f,
		0,
		false);
}

void Timer::Update() {
	Uint32 now = SDL_GetTicks();
	if (m_Selected) {
		m_StartTime = now - m_ElapsedTime;
		m_PauseIcon->SetTexture("timer_continue");
	}
	else {
		Uint32 elapsed_time = now - m_StartTime;
		if (elapsed_time / 1000 != m_ElapsedTime / 1000) { IncreaseTime(); }
		m_ElapsedTime = elapsed_time;
		m_PauseIcon->SetTexture("timer_pause");
	}
}

void Timer::Draw()
{
	Button::Draw();
	m_Clock->Draw();
	m_PauseIcon->Draw();
}

void Timer::IncreaseTime()
{
	m_Clock->DestroyTexture();

	// Convert from milisecond to second
	int seconds = (m_ElapsedTime / 1000) % 60;
	int minutes = m_ElapsedTime / 60000;
	std::string now = std::to_string(minutes / 10)
		+ std::to_string(minutes % 10)
		+ ":"
		+ std::to_string(seconds / 10)
		+ std::to_string(seconds % 10);

	m_Clock->SetTexture(TextureManager::GetInstance()->CreateTextureFromString(now, Color::pencil_gray));
}
