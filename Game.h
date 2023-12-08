
#ifndef GAME_H_
#define GAME_H_


//include all
#include <stdio.h>
#include "SDL.h"


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


private:
	Game()
	{
		m_Window = nullptr;
		m_Renderer = nullptr;
		m_IsRunning = false;
	}

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;

	static Game* s_Instance;
};

#endif // !GAME_H_

