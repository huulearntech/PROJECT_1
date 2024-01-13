
#ifndef GAME_H_
#define GAME_H_


//include all
#include <stdio.h>
#include "SDL.h"
#include "TextureManager.h"
#include "GameControlsWrapper.h"
#include "BoardWrapper.h"
#include "Numpad.h"
#include "Timer.h"
#include "ChooseLevelPage.h"

constexpr int GAME_WIDTH = 960;	
constexpr int GAME_HEIGHT = 640;


class Game
{
public:
	static Game* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game(); }

	inline bool IsRunning() const { return m_IsRunning; }

	inline SDL_Window* GetWindow() const { return m_Window; }

	inline SDL_Renderer* GetRenderer() const { return m_Renderer; }

	bool Init();

	void Play();

	void HandleEvents();

	void Update();

	void Render();
	
	void Close();

	void Clean();

	friend class EventHandler;

private:
	Game()
	{
		m_Window = nullptr;
		m_Renderer = nullptr;
		m_IsRunning = false;
		m_ControlsWrapper = nullptr;
		m_Numpad = nullptr;
		m_BoardWrapper = nullptr;
		m_ChooseLevelPage = nullptr;
	}

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;

	BoardWrapper* m_BoardWrapper;
	
	GameControlsWrapper* m_ControlsWrapper;

	Numpad* m_Numpad;

	ChooseLevelPage* m_ChooseLevelPage;

	static Game* s_Instance;
};

#endif // !GAME_H_

