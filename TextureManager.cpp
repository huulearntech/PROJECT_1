#include "TextureManager.h"
#include "Game.h"


TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Init()
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG ;
    IMG_Init(flags);
    if ((flags & IMG_Init(flags)) != flags) {
        printf("Failed initialize TextureManager: %s, at location: %s\n", SDL_GetError(), __FILE__);
        return false;
    }
    return true;
}

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

void TextureManager::Draw(std::string textureId, SDL_Rect destRect)
{
    SDL_Rect srcRect = { 0, 0, 0, 0 };
    SDL_QueryTexture(TextureManager::GetInstance()->m_TextureMap[textureId], NULL, NULL, &(srcRect.w), &(srcRect.h));
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_TextureMap[textureId], &srcRect, &destRect);
}

void TextureManager::Drop(std::string textureId)
{
    SDL_DestroyTexture(m_TextureMap[textureId]);
    m_TextureMap.erase(textureId);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++) {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
    printf("All textures cleaned!");
}

SDL_Texture* TextureManager::GetTexture(std::string textureID)
{
    if (m_TextureMap.find(textureID) != m_TextureMap.end()) {
        return m_TextureMap[textureID];
    }
    return nullptr;
}
