

// This is the Main Engine for the Sudoku Game
// Created in Dec 2 2023 for Project 1 by Trinh Phuc Huu 20215596 SOICT HUST VN

#include "Game.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Button.h"
#include "Box.h"

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
        // | SDL_WINDOW_RESIZABLE                           // WINDOW FLAGS, SEE SDL_WINDOW_FLAGS
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

    SDL_Surface* icon = SDL_LoadBMP("sudoku_icon.bmp");
    if (icon == nullptr) {
        SDL_Log("Error initializing Game Icon: %s; at location %s", SDL_GetError(), __FILE__);
        return false;
    }
    SDL_SetWindowIcon(m_Window, icon);
    SDL_FreeSurface(icon);


    if (!TextureManager::GetInstance()->Init() || EventHandler::GetInstance() == nullptr) 
    {
        return false;
    }

    return m_IsRunning = true;
}

void Game::Play()
{
    Button* button = new Button({ 100, 100, 100, 100 });
    Box* box = new Box({ 200, 200, 100, 100 }, 6, 6);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);

    while (Game::IsRunning()) {
        //Game::HandleEvents();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                Game::GetInstance()->Close();
            }
            button->HandleEvent(event);
            button->Draw();
            box->HandleEvent(event);
            box->Draw();
            Game::Update();
            Game::Render();
        }
    }
}

void Game::HandleEvents()
{
    EventHandler::GetInstance()->Listen();
}
void Game::Update()
{
    if (EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        printf("A");
    }
    //all components::Update()
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
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    SDL_Quit();
}
