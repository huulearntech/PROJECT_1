#pragma once
#ifndef NUMPAD_H_
#define NUMPAD_H_

#include "BaseObject.h"
#include "FillNumber.h"

const int NumpadPos[3] = {0, 70, 140};


class Numpad : public BaseObject
{
public:
	Numpad(SDL_Rect rect);

	int GetNumber();
	void Init(int boardState);
	void HandleMouseDown(SDL_Event& event);
	void HandleMouseUp();
	void HandleMouseMotion(SDL_Event& event);
	void SetRemainNumbers(int boardState);
	void Draw();
	void Update();


private:
	FillNumber* m_Numpad[9] = { nullptr };
};


#endif // !NUMPAD_H_
