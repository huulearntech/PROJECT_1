
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
        printf("Failed initialize TextureManager: %s, at location: %s\n", IMG_GetError(), __FILE__);
        return false;
    }

    TextureManager::LoadNumbers();
    TextureManager::GetInstance()->Load("hint_3", "assets/hint_3.png");
    TextureManager::GetInstance()->Load("hint_2", "assets/hint_2.png");
    TextureManager::GetInstance()->Load("hint_1", "assets/hint_1.png");
    TextureManager::GetInstance()->Load("hint_0", "assets/hint_0.png");
    TextureManager::GetInstance()->Load("pencil_on", "assets/pencil_on.png");
    TextureManager::GetInstance()->Load("pencil_off", "assets/pencil_off.png");
    TextureManager::GetInstance()->Load("board", "assets/board.png");   

    return true;
}

// Load textures of icons
bool TextureManager::Load(std::string textureId, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed loading surface: %s, %s\n", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr) {
        SDL_Log("Failed create texture from surface: %s, %s\n", filename.c_str(), SDL_GetError());
        return false;
    }

    m_TextureMap[textureId] = texture;
    SDL_FreeSurface(surface);

    return true;
}

// Load all numbers of categories: const, correct, wrong
void TextureManager::LoadNumbers()
{
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    std::string textureID = "";
    for (int i = 1; i <= 9; i++) {
        textureID = "const_" + std::to_string(i);
        surface = IMG_Load(("assets/" + textureID + ".png").c_str());
        texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
        TextureManager::GetInstance()->m_TextureMap[textureID] = texture;
    }

    for (int i = 1; i <= 9; i++) {
        textureID = "correct_" + std::to_string(i);
        surface = IMG_Load(("assets/" + textureID + ".png").c_str());
        texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
        TextureManager::GetInstance()->m_TextureMap[textureID] = texture;
    }
    
    for (int i = 1; i <= 9; i++) {
        textureID = "wrong_" + std::to_string(i);
        surface = IMG_Load(("assets/" + textureID + ".png").c_str());
        texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
        TextureManager::GetInstance()->m_TextureMap[textureID] = texture;
    }
    for (int i = 1; i <= 9; i++) {
        textureID = "pencil_" + std::to_string(i);
        surface = IMG_Load(("assets/" + textureID + ".png").c_str());
        texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
        TextureManager::GetInstance()->m_TextureMap[textureID] = texture;
    }
    SDL_FreeSurface(surface);
}

// Draw numbers, icons
void TextureManager::Draw(std::string textureId, SDL_Rect destRect)
{
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_TextureMap[textureId], nullptr, &destRect);
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

    // Free IMG
    IMG_Quit();
}
