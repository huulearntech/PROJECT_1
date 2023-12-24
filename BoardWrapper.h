#pragma once

#ifndef BOARDWRAPPER_H_
#define BOARDWRAPPER_H_


#include "Board.h"
#include "Timer.h"
#include "TextureManager.h"

class BoardWrapper : BaseObject
{
public:
	BoardWrapper(SDL_Rect rect) : BaseObject(rect) {
		m_Board = new Board({ rect.x, rect.y + 100, rect.w, rect.h });
		m_Timer = new Timer({ rect.x, rect.y, 100, 100 }, Color::white, Color::dark_gray, Color::light_gray);
		m_LevelLabel = nullptr;
		m_MistakeLabel = nullptr;
	}

	bool Init(std::string level);

	void HandleMouseDown(SDL_Event& event);
	void HandleMouseMotion(SDL_Event& event);

	void Draw();
	void Update();

private:
	Board* m_Board;
	Timer* m_Timer;
	SDL_Texture* m_LevelLabel;
	SDL_Texture* m_MistakeLabel;
};

#endif // !BOARDWRAPPER_H_
