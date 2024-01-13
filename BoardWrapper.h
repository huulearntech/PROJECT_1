#pragma once

#ifndef BOARDWRAPPER_H_
#define BOARDWRAPPER_H_


#include "Board.h"
#include "Timer.h"
#include "Texture.h"
#include "TextureManager.h"

class BoardWrapper : BaseObject
{
public:
	BoardWrapper(SDL_Rect rect);

	bool Init(std::string level);

	void HandleMouseDown(SDL_Event& event);
	void HandleMouseMotion(SDL_Event& event);

	inline Board* GetBoard() const { return m_Board; }

	void Draw();
	void Update();

	inline bool GameOver() const { return m_Board->GetMistakeCount() >= m_MistakeLimit; }
	inline bool GameComplete() const { return m_Board->GetState() == 0; }

private:
	Board* m_Board;
	Timer* m_Timer;
	Texture* m_LevelLabel;
	Texture* m_MistakeLabel;



	int m_MistakeLimit;
};

#endif // !BOARDWRAPPER_H_
