
// This is the Main Engine for the Sudoku Game
// Created in Dec 2 2023 for Project 1 by Trinh Phuc Huu 20215596 SOICT HUST VN

#include "Game.h"
#include "TextureManager.h"
#include "EventHandler.h"

Game* Game::s_Instance = nullptr;

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { 
        SDL_Log("Error initializing SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow(
        "Sudoku",                                           // TITLE
        SDL_WINDOWPOS_CENTERED,                             // POSITION CENTERED
        SDL_WINDOWPOS_CENTERED,
        GAME_WIDTH,                                         // 960 BY DEFAULT
        GAME_HEIGHT,                                        // 640 BY DEFAULT
        SDL_WINDOW_MAXIMIZED
        | SDL_WINDOW_RESIZABLE                              // WINDOW FLAGS, SEE SDL_WINDOW_FLAGS
    );

    if (m_Window == nullptr) {
        SDL_Log("Error initializing Game Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(
        m_Window,                                               // TARGET
        -1,                                                     // THE FIRST RENDERER
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE   // RENDERER FLAGS
    );

    if (m_Renderer == nullptr) {
        SDL_Log("Error initializing Game Renderer: %s", SDL_GetError());
        return false;
    }

    SDL_Surface* icon = SDL_LoadBMP("assets/sudoku_icon.bmp");
    if (icon == nullptr) {
        SDL_Log("Error initializing Game Icon: %s", SDL_GetError());
        return false;
    }
    SDL_SetWindowIcon(m_Window, icon);
    SDL_FreeSurface(icon);


    if (!TextureManager::GetInstance()->Init()) 
    {
        return false;
    }

    m_Board->Init(Level::easy);
    
    return m_IsRunning = true;
}

void Game::Play()
{
    while (Game::IsRunning()) {
        Game::HandleEvents();
        Game::Update();
        Game::Render();
    }
}

void Game::HandleEvents()
{
    if (m_Board->GameOver()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, nullptr, "Game over!", Game::GetInstance()->GetWindow());
        Game::Close();
    }
    if (m_Board->IsCompleted()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, nullptr, "Congratulation, you won!", Game::GetInstance()->GetWindow());
        Game::Close();
    }
    EventHandler::GetInstance()->Listen();
}

void Game::Update()
{
    EventHandler::GetInstance()->Update(m_Board, m_ControlsWrapper, m_Numpad);
    m_Board->Update();
    m_ControlsWrapper->Update();
    m_Numpad->Update();
    m_Timer->Update();
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);
    m_Board->Draw();
    m_ControlsWrapper->Draw();
    m_Numpad->Draw();
    m_Timer->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Game::Close()
{
    m_IsRunning = false;
}

void Game::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    SDL_Quit();
}
