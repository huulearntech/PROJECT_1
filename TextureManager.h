#pragma once

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <map>


namespace Color
{
	const SDL_Color white = { 255, 255, 255 };
	const SDL_Color black = { 0, 0, 0 };
	const SDL_Color light_gray = { 234, 238, 244 };
	const SDL_Color gray = { 220, 227, 237 };
	const SDL_Color dark_gray = { 210, 218, 231 };
	const SDL_Color pencil_gray = { 110, 124, 140 };
	const SDL_Color red = { 229, 92, 108 };
	const SDL_Color pink = { 247, 207, 214 };
	const SDL_Color cyan = { 187, 222, 251 };
	const SDL_Color light_cyan = { 226, 235, 243 };
	const SDL_Color blue = { 50, 90, 175 };
	const SDL_Color gray_blue = { 52, 72, 97 };
}


class TextureManager
{
public:
	static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }
	
	bool Init();
	inline TTF_Font* GetFont() const { return m_Font; }
	bool Load(std::string textureId, std::string filename);
	void LoadNumbers();
	SDL_Texture* CreateTextureFromString(std::string text, SDL_Color textColor);

	inline SDL_Texture* GetTexture(std::string textureID) const { return m_TextureMap.at(textureID); }
	void Draw(SDL_Texture* texture, SDL_Rect destRect);
	void Draw(std::string textureId, SDL_Rect destRect);
	void Draw(SDL_Color color, SDL_Rect destRect);
	void Clean();

private:
	TextureManager() { m_Font = nullptr; }
	static TextureManager* s_Instance;
	std::map<std::string, SDL_Texture*> m_TextureMap;
	TTF_Font* m_Font;
};


#endif // !TEXTUREMANAGER_H_
