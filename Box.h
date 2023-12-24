#pragma once
#ifndef BOX_H_
#define BOX_H_

#include "Button.h"
#include "Label.h"

class Box : public Button
{
private:
	int m_HoldingNumber;
	int m_CorrectNumber;
	bool m_IsGiven;
	std::string m_TextureID;
	Label* m_NumberLabel;
	bool m_Draft[9] = { false };
	Label* m_DraftLabel[9] = { nullptr };

public:
	Box(SDL_Rect rect, SDL_Color normalColor, SDL_Color selectColor, SDL_Color hoverColor, int number, int correctNumber);

	void SetNumber(int number);
	void SetDraftNumber(int number);
	inline bool IsCorrect() const { return m_HoldingNumber == m_CorrectNumber; }
	inline int GetHoldingNumber() const { return m_HoldingNumber; }
	inline int GetCorrectNumber() const { return m_CorrectNumber; }

	bool ShowHint();

	void Update();
	void Draw();

	Uint16 Encode() const;
	void Decode(Uint16 code);
};

#endif // !BOX_H_
