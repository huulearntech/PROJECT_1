
#ifndef GAME_H_
#define GAME_H_


//include all
#include <stdio.h>
#include "SDL.h"
#include "Board.h"
#include "FunctionButton.h"
#include "Pencil.h"


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

	void HandleEvents(SDL_Event event);

	void Render();
	
	void Close();

	void Clean();


private:
	Game()
	{
		m_Window = nullptr;
		m_Renderer = nullptr;
		m_IsRunning = false;

		m_Board = new Board({ 50, 50, BOARD_SIZE_IN_PX, BOARD_SIZE_IN_PX });
		m_HintButton = new FunctionButton({ 800, 300, 60, 60 });
		m_Pencil = new Pencil({ 800, 400, 60, 60 });
	}

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;

	Board* m_Board;
	
	FunctionButton* m_HintButton;

	Pencil* m_Pencil;
	

	static Game* s_Instance;
};

#endif // !GAME_H_

