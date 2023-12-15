

// This is the Main Engine for the Sudoku Game
// Created in Dec 2 2023 for Project 1 by Trinh Phuc Huu 20215596 SOICT HUST VN

#include "Game.h"
#include "TextureManager.h"

Game* Game::s_Instance = nullptr;

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { 
        SDL_Log("Error initializing SDL: %s; at location %s", SDL_GetError(), __FILE__);
        return false;
    }

    m_Window = SDL_CreateWindow(
        "Sudoku",                                           // TITLE
        SDL_WINDOWPOS_CENTERED,                             // POSITION CENTERED
        SDL_WINDOWPOS_CENTERED,
        GAME_WIDTH,                                         // 960 BY DEFAULT
        GAME_HEIGHT,                                        // 640 BY DEFAULT
        SDL_WINDOW_MAXIMIZED
        //| SDL_WINDOW_RESIZABLE                           // WINDOW FLAGS, SEE SDL_WINDOW_FLAGS
    );

    if (m_Window == nullptr) {
        SDL_Log("Error initializing Game Window: %s; at location %s", SDL_GetError(), __FILE__);
    }

    m_Renderer = SDL_CreateRenderer(
        m_Window,                                               // TARGET
        -1,                                                     // THE FIRST RENDERER
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE   // RENDERER FLAGS
    );

    if (m_Renderer == nullptr) {
        SDL_Log("Error initializing Game Renderer: %s; at location %s", SDL_GetError(), __FILE__);
        return false;
    }

    SDL_Surface* icon = SDL_LoadBMP("assets/sudoku_icon.bmp");
    if (icon == nullptr) {
        SDL_Log("Error initializing Game Icon: %s; at location %s", SDL_GetError(), __FILE__);
        return false;
    }
    SDL_SetWindowIcon(m_Window, icon);
    SDL_FreeSurface(icon);


    if (!TextureManager::GetInstance()->Init()) 
    {
        return false;
    }

    m_Board->Init(LEVEL::EASY);

    return m_IsRunning = true;
}

void Game::Play()
{
    while (Game::IsRunning()) {
        //Game::HandleEvents();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
            SDL_RenderClear(m_Renderer);

            Game::HandleEvents(event);
            m_Board->Draw();
            m_HintButton->Draw();
            m_Pencil->Draw();
            Game::Render();
        }
    }
}

void Game::HandleEvents(SDL_Event event)
{
    if (event.type == SDL_QUIT) {
        Game::GetInstance()->Close();
    }

    m_Board->HandleEvent(event);
    m_HintButton->HandleEvent(event, m_Board);
    m_Pencil->HandleEvent(event, m_Board);
}

void Game::Render()
{
    //SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    //SDL_RenderClear(m_Renderer);
    //Here means do something with renderer base on Event
    //Board::Draw();
    SDL_RenderPresent(m_Renderer);
}

void Game::Close()
{
    m_IsRunning = false;
}

void Game::Clean()
{
    TextureManager::GetInstance()->Clean();
    m_Board->~Board();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    SDL_Quit();
}
