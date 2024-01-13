#include "BoardWrapper.h"

BoardWrapper::BoardWrapper(SDL_Rect rect) : BaseObject(rect) {
	m_Board = new Board({ rect.x, rect.y + 50, rect.w, rect.h });
	m_Timer = new Timer({ rect.x + 230, rect.y, 100, 30 }, Color::white, Color::dark_gray, Color::light_gray);
	m_LevelLabel = nullptr;
	m_MistakeLabel = nullptr;
	m_MistakeLimit = 3;
}

bool BoardWrapper::Init(std::string level)
{
	m_Board->Reset();
	// Specify filepath
	std::string filepath = level + "_database.txt";
	m_Board->LoadData(filepath);


	// Set label
	m_LevelLabel = new Texture({ 500, 0, 100, 30 },
		TextureManager::GetInstance()->CreateTextureFromString(level, Color::pencil_gray),
		0.5f);

	m_MistakeLabel = new Texture(m_Rect,
		TextureManager::GetInstance()->CreateTextureFromString("Mistake: 0 / "
			+ std::to_string(m_MistakeLimit), Color::pencil_gray),
		0.25f,
		0.05f,
		0,
		0.01f,
		false);

	return true;
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
	m_LevelLabel->Draw();
	m_MistakeLabel->Draw();
}

void BoardWrapper::Update()
{
	if (m_Timer->IsSelected()) { m_Board->SetHidden(true); }
	else m_Board->SetHidden(false);
	if (m_Board->MakeMistake()) {
		m_MistakeLabel->DestroyTexture();
		m_MistakeLabel->SetTexture(TextureManager::GetInstance()->CreateTextureFromString("Mistake: "
			+ std::to_string(m_Board->GetMistakeCount())
			+ " / "
			+ std::to_string(m_MistakeLimit), Color::pencil_gray));
	}
	m_Timer->Update();
	m_Board->Update();
}
