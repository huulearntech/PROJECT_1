
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

    if (!TextureManager::GetInstance()->Init()) 
    {
        return false;
    }

    m_ChooseLevelPage = new ChooseLevelPage({ 500, 400, 200, 200 });
    m_BoardWrapper = new BoardWrapper({ 50, 0, BOARD_SIZE_IN_PX, BOARD_SIZE_IN_PX });
    m_ControlsWrapper = new GameControlsWrapper({ 800, 100, 200, 60 }, Color::light_gray, Color::dark_gray, Color::gray);
    m_Numpad = new Numpad({ 800, 200, 180, 180 });   

    m_BoardWrapper->Init(Level::easy);
    m_BoardWrapper->Update();
    m_Numpad->Init(m_BoardWrapper->GetBoard()->GetState());
    
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
    EventHandler::GetInstance()->Listen();
}

void Game::Update()
{
    // Check game over
    if (m_BoardWrapper->GameOver()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game over", "You made 3 mistakes", m_Window);
        Close();
    }
    
    // Check win
    if (m_BoardWrapper->GameComplete()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You won!", "Congratulation!", m_Window);
        Close();
    }

    if (m_ChooseLevelPage->IsActivate()) {
        m_ChooseLevelPage->Update();
    }
    else {
        EventHandler::GetInstance()->Update(m_BoardWrapper, m_ControlsWrapper, m_Numpad);
        m_BoardWrapper->Update();
        m_ControlsWrapper->Update();
        m_Numpad->Update();
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);
    if (m_ChooseLevelPage->IsActivate()) {
        m_ChooseLevelPage->Draw();
    }
    else {
        m_BoardWrapper->Draw();
        m_ControlsWrapper->Draw();
        m_Numpad->Draw();
    }
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
