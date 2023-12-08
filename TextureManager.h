#pragma once

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class TextureManager
{
public:
	static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }
	
	bool Init();
	bool Load(std::string textureId, std::string filename);
	void Draw(std::string id, SDL_Rect destRect);
	void Drop(std::string id);
	void Clean();

	SDL_Texture* GetTexture(std::string textureID);


private:
	TextureManager() {}
	static TextureManager* s_Instance;
	std::map<std::string, SDL_Texture*> m_TextureMap;
};


#endif // !TEXTUREMANAGER_H_
