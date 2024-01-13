
#include "TextureManager.h"

// SDL_image.h for rendering all images, icons
#include "SDL_image.h"


// Game.h for Renderer usage
#include "Game.h"

TextureManager* TextureManager::s_Instance = nullptr;

// Initialization
bool TextureManager::Init()
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG ;
    IMG_Init(flags);
    if ((flags & IMG_Init(flags)) != flags) {
        printf("Failed initialize TextureManager: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        SDL_Log(TTF_GetError());
    }

    m_Font = TTF_OpenFont("font/Roboto-Regular.ttf", 60);

    TextureManager::LoadNumbers();
    TextureManager::Load("hint_3", "assets/hint_3.png");
    TextureManager::Load("hint_2", "assets/hint_2.png");
    TextureManager::Load("hint_1", "assets/hint_1.png");
    TextureManager::Load("hint_0", "assets/hint_0.png");
    TextureManager::Load("pencil_on", "assets/pencil_on.png");
    TextureManager::Load("pencil_off", "assets/pencil_off.png");
    TextureManager::Load("eraser", "assets/eraser.png");
    TextureManager::Load("board", "assets/board.png");   
    TextureManager::Load("board_hidden", "assets/board2.png");   
    TextureManager::Load("timer_pause", "assets/timer_pause.png");
    TextureManager::Load("timer_continue", "assets/timer_continue.png");
    TextureManager::Load("logo", "assets/logo.png");
    
    m_TextureMap["choose_level"] = TextureManager::CreateTextureFromString("Please choose level", Color::black);

    return true;
}

// Load textures of icons
bool TextureManager::Load(std::string textureID, std::string filename)
{
    m_TextureMap[textureID] = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), filename.c_str());
    return m_TextureMap[textureID] != nullptr;
}

// Load all numbers of categories: const, correct, wrong, pencil
void TextureManager::LoadNumbers()
{
    for (int i = 1; i <= 9; i++) {
        std::string str_num = std::to_string(i);

        // Load const
        TextureManager::GetInstance()->m_TextureMap["const_" + str_num]
            = CreateTextureFromString(str_num, Color::gray_blue);
        
        // Load correct
        TextureManager::GetInstance()->m_TextureMap["correct_" + str_num]
            = CreateTextureFromString(str_num, Color::blue);

        // Load wrong
        TextureManager::GetInstance()->m_TextureMap["wrong_" + str_num]
            = CreateTextureFromString(str_num, Color::red);

        // Load pencil
        TextureManager::GetInstance()->m_TextureMap["pencil_" + str_num]
            = CreateTextureFromString(str_num, Color::pencil_gray);
    }
    TextureManager::GetInstance()->m_TextureMap["pencil_0"]
        = CreateTextureFromString("0", Color::pencil_gray);
}

SDL_Texture* TextureManager::CreateTextureFromString(std::string text, SDL_Color textColor)
{
    SDL_Surface* surface = TTF_RenderText_Blended(m_Font, text.c_str(), textColor);
    if (surface == nullptr) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
    SDL_FreeSurface(surface);
    return texture;
}


void TextureManager::Draw(SDL_Texture* texture, SDL_Rect destRect)
{
    if (texture != nullptr) {
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, nullptr, &destRect);
    }
}
//
//void TextureManager::Draw(SDL_Texture* texture, SDL_Rect destRect, float scaleX = 1, float scaleY = 1)
//{
//    if (scaleX != 1.0f || scaleY != 1.0f) {
//        SDL_Rect rect = { destRect.x + (int)(destRect.w * (0.5f - scaleX)),
//            destRect.y + (int)(destRect.h * (0.5f - scaleY)),
//            (int)(destRect.w * scaleX),
//            (int)(destRect.h * scaleY),
//        };
//        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, nullptr, &rect);
//    }
//    else {
//        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, nullptr, &destRect);
//    }
//}

// Draw numbers, icons, labels
void TextureManager::Draw(std::string textureId, SDL_Rect destRect)
{
    if (textureId != "") {
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_TextureMap[textureId], nullptr, &destRect);
    }
}

// Draw backgrounds
void TextureManager::Draw(SDL_Color color, SDL_Rect destRect)
{
    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &destRect);
}

// Free resources
void TextureManager::Clean()
{
    // Free all textures
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++) {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
    printf("All textures cleaned!");

    // Free IMG & TTF
    IMG_Quit();
    TTF_CloseFont(m_Font);
    TTF_Quit();
}
