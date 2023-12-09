#pragma once

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <stdio.h>
#include "SDL.h"
#include <string>
#include <map>

class TextureManager
{
public:
	static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }
	
	bool Init();
	bool Load(std::string textureId, std::string filename);
	void LoadNumbers();
	void Draw(std::string textureId, SDL_Rect destRect);
	void Draw(SDL_Color color, SDL_Rect destRect);
	void Clean();

private:
	TextureManager() {}
	static TextureManager* s_Instance;
	std::map<std::string, SDL_Texture*> m_TextureMap;
};


#endif // !TEXTUREMANAGER_H_
