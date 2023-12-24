
#ifndef GAME_H_
#define GAME_H_


//include all
#include <stdio.h>
#include "SDL.h"
#include "Board.h"
#include "TextureManager.h"
#include "GameControlsWrapper.h"
#include "Numpad.h"
#include "Timer.h"

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

		m_Board = new Board({ 50, 50, BOARD_SIZE_IN_PX, BOARD_SIZE_IN_PX });
		m_ControlsWrapper = new GameControlsWrapper({ 800, 100, 200, 60 }, Color::light_gray, Color::dark_gray, Color::gray);
		m_Numpad = new Numpad({ 800, 200, 180, 180 });
		m_Timer = new Timer({ 400, 0, 72, 30 }, Color::white, Color::dark_gray, Color::gray);
	}

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;

	Board* m_Board;
	
	GameControlsWrapper* m_ControlsWrapper;

	Timer* m_Timer;

	Numpad* m_Numpad;

	static Game* s_Instance;
};

#endif // !GAME_H_

