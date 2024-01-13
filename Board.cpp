
#include "Board.h"
#include <random>
#include "TextureManager.h"
#include "EventHandler.h"
#include <math.h>


bool Board::LoadData(std::string filepath)
{
	// Open data file
	FILE* fptr;
	if (fopen_s(&fptr, filepath.c_str(), "r") != 0) {
		printf("Failed in loading board data: Can't open file %s\n", filepath.c_str());
		return false;
	}

	// Select random game from database
	srand((unsigned int)time(NULL));
	fseek(fptr, (rand() % NUMBER_OF_RECORDS) * RECORD_SIZE, SEEK_SET);

	// Load numbers from chosen game
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			int number = fgetc(fptr) - '0';
			int correctNumber = fgetc(fptr) - '0';
			printf("%d ", correctNumber);
			if (number < 0 || number > 9 || correctNumber < 0 || correctNumber > 9)
			{
				printf("Incorrect data at position %ld of file %s\n", ftell(fptr), filepath.c_str());
				fclose(fptr);
				fptr = nullptr;
				return false;
			}
			SDL_Rect boxRect = { m_Rect.x + BoxesCoordinates[j], m_Rect.y + BoxesCoordinates[i], BOX_SIZE_IN_PX, BOX_SIZE_IN_PX };
			m_Board[i][j] = new Box(boxRect, Color::white, Color::cyan, Color::gray, number, correctNumber);
		}
		printf("\n");
	}

	// Close data file and return true on success
	fclose(fptr);
	fptr = nullptr;
	return true;
}

void Board::Draw()
{
	TextureManager::GetInstance()->Draw(m_TextureID, Board::m_Rect);
	if (!m_IsHidden) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				m_Board[i][j]->Draw();
			}
		}
	}
}

void Board::Reset()
{
	m_CurrRow = m_CurrCol = UNDEFINED;
	m_MistakeCount = 0;
	m_IsHidden = false;
	m_TextureID = "board";
	m_MakeMistake = false;

	m_State = 999999999;
}


void Board::HandleMouseDown(SDL_Event& event)
{
	if (Board::MouseIsWithin(event.motion.x, event.motion.y)) {
		if (m_IsHidden) { m_IsHidden = false; }
		else {
			m_CurrRow = m_CurrCol = UNDEFINED;
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < BOARD_SIZE; j++) {
					m_Board[i][j]->HandleMouseDown(event);
					if (m_Board[i][j]->IsSelected()) {
						m_CurrRow = i;
						m_CurrCol = j;
					}
				}
			}
		}
	}
}

void Board::HandleMouseMotion(SDL_Event& event)
{
	if (!m_IsHidden) {
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				m_Board[i][j]->HandleMouseMotion(event);
			}
		}
	}
}

void Board::SetNumber(int number)
{
	if (m_CurrRow != UNDEFINED && m_CurrCol != UNDEFINED) {
		if (m_Board[m_CurrRow][m_CurrCol]->GetHoldingNumber() != number) {
			m_Board[m_CurrRow][m_CurrCol]->SetNumber(number);
			if (number > 0 && !m_Board[m_CurrRow][m_CurrCol]->IsCorrect()) {
				m_MistakeCount++;
				m_MakeMistake = true;
			}
		}
	}
}

void Board::Highlight()
{
	if (m_CurrRow != UNDEFINED && m_CurrCol != UNDEFINED) {
		// Highlight row and column
		for (int i = 0; i < BOARD_SIZE; i++) {
			m_Board[i][m_CurrCol]->SetColor(Color::light_cyan);
			m_Board[m_CurrRow][i]->SetColor(Color::light_cyan);
		}

		// Highlight 3x3 block
		int blockX = m_CurrRow - m_CurrRow % 3;
		int blockY = m_CurrCol - m_CurrCol % 3;
		for (int i = blockX; i < blockX + 3; i++) {
			for (int j = blockY; j < blockY + 3; j++) {
				m_Board[i][j]->SetColor(Color::light_cyan);
			}
		}

		// Highlight same numbers
		int currentNumber = m_Board[m_CurrRow][m_CurrCol]->GetHoldingNumber();
		if (currentNumber > 0) {
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < BOARD_SIZE; j++) {
					if (m_Board[i][j]->GetHoldingNumber() == m_Board[m_CurrRow][m_CurrCol]->GetHoldingNumber()) {
						m_Board[i][j]->SetColor(Color::cyan);
					}
				}
			}
		}
		m_Board[m_CurrRow][m_CurrCol]->Update();
	}
}

// Suggest related cells
void Board::Update()
{
	if (m_IsHidden) { m_TextureID = "board_hidden"; }
	else {
		m_State = 999999999;
		m_TextureID = "board";
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				m_Board[i][j]->Update();
				if (m_Board[i][j]->IsCorrect()) {
					m_State -= pow(10, m_Board[i][j]->GetCorrectNumber() - 1);
				}
			}
		}
		Highlight();
	}
	m_MakeMistake = false;
}