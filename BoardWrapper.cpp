#include "BoardWrapper.h"

bool BoardWrapper::Init(std::string level)
{
	// Specify filepath
	std::string filepath = level + "_database";

	// Set label
	m_LevelLabel = TextureManager::GetInstance()->CreateTextureFromString(level, Color::black);
	return false;
}

void BoardWrapper::HandleMouseDown(SDL_Event& event)
{
	m_Board->HandleMouseDown(event);
	m_Timer->HandleMouseDown(event);
}

void BoardWrapper::HandleMouseMotion(SDL_Event& event)
{
	m_Board->HandleMouseMotion(event);
	m_Timer->HandleMouseMotion(event);
}

void BoardWrapper::Draw()
{
	m_Board->Draw();
	m_Timer->Draw();
}

void BoardWrapper::Update()
{
	if (m_Timer->IsSelected()) m_Board->SetHidden(true);
	else m_Board->SetHidden(false);
	m_Timer->Update();
	m_Board->Update();
}
