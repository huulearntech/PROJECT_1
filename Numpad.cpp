#include "Numpad.h"
#include "TextureManager.h"

Numpad::Numpad(SDL_Rect rect) : BaseObject(rect)
{
	int width = rect.w / 3;
	int height = rect.h / 3;
	for (int i = 0; i < 9; i++) {
		SDL_Rect numberRect = { rect.x + NumpadPos[i % 3], rect.y + NumpadPos[i / 3], width, height };
		m_Numpad[i] = new FillNumber(numberRect, Color::light_gray, Color::dark_gray, Color::gray, i+1, 9);
	}
}

int Numpad::GetNumber() {
	for (int i = 0; i < 9; i++) {
		if (m_Numpad[i]->OnClick()) return i + 1;
	}
	return -1;
}

void Numpad::Init(int boardState)
{
	for (int i = 0; i <= 8; i++) {
		m_Numpad[i]->SetRemain(boardState % 10);
		boardState /= 10;
	}
}

void Numpad::HandleMouseDown(SDL_Event& event)
{
	if (Numpad::MouseIsWithin(event.motion.x, event.motion.y)) {
		for (int i = 0; i < 9; i++) {
			m_Numpad[i]->HandleMouseDown(event);
		}
	}
}

void Numpad::HandleMouseUp()
{
	for (int i = 0; i < 9; i++) {
		m_Numpad[i]->SetSelect(false);
	}
}

void Numpad::HandleMouseMotion(SDL_Event& event)
{
	for (int i = 0; i < 9; i++) {
		m_Numpad[i]->HandleMouseMotion(event);
	}
}

void Numpad::SetRemainNumbers(int boardState)
{
	for (int i = 0; i <= 8; i++) {
		m_Numpad[i]->SetRemain(boardState % 10);
		boardState /= 10;
	}
}

void Numpad::Draw()
{
	for (int i = 0; i < 9; i++) {
		m_Numpad[i]->Draw();
	}
}

void Numpad::Update()
{
	for (int i = 0; i < 9; i++) {
		m_Numpad[i]->Update();
	}
}
