#pragma once

#ifndef GAMECONTROLSWRAPPER_H_
#define GAMECONTROLSWRAPPER_H_

#include "Button.h"
#include "HintButton.h"

namespace GameMode
{
	const Uint8 PENCIL = (1 << 0);
	const Uint8 ERASER = (1 << 1);
	const Uint8 HINT = (1 << 2);
};


class GameControlsWrapper : public BaseObject
{
public:
	GameControlsWrapper(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor);

	void HandleMouseDown(SDL_Event& event);
	void HandleMouseMotion(SDL_Event& event);

	void Draw();
	void Update();

	inline HintButton* GetHintButton() const { return m_Hint; }

	inline Uint8 GetState() const { return m_State; }

private:
	Button* m_Pencil;
	Button* m_Eraser;
	HintButton* m_Hint;

	Uint8 m_State;
};



#endif // !GAMECONTROLSWRAPPER_H_
