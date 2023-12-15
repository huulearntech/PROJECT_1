#include "Game.h"
#include "TextureManager.h"
#include "Board.h"
#include <random>

bool Board::Init(LEVEL level)
{
	if (Board::LoadData(level) == false) { return false; }
	Board::Draw();
	return true;
}

bool Board::LoadData(LEVEL level)
{
	// Specify filepath
	std::string filepath;
	switch (level)
	{
	case LEVEL::EASY:
		filepath = "easy_database.txt";
		break;
	case LEVEL::MEDIUM:
		filepath = "medium_database.txt";
		break;
	case LEVEL::HARD:
		filepath = "hard_database.txt";
		break;
	case LEVEL::EXTREME:
		filepath = "extreme_database.txt";
		break;
	default:
		break;
	}

	// Open data file
	FILE* fptr;
	if (fopen_s(&fptr,filepath.c_str(), "r") != 0) {
		printf("Failed in loading board data: Can't open file %s\n", filepath.c_str());
		return false;
	}

	// Select random game from database
	srand((unsigned int) time(NULL));
	fseek(fptr, (rand() % NUMBER_OF_RECORDS) * RECORD_SIZE, SEEK_SET);

	// Load numbers from chosen game
	int number, correctNumber;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			number = fgetc(fptr) - '0';
			correctNumber = fgetc(fptr) - '0';
			printf("%d ", correctNumber);
			if (number < 0 || number > 9 ||
				correctNumber < 0 || correctNumber > 9)
			{
				printf("Incorrect data at position %ld of file %s\n", ftell(fptr), filepath.c_str());
				fclose(fptr);
				fptr = nullptr;
				return false;
			}
			SDL_Rect boxRect = {Board::m_Rect.x + j * BOX_SIZE_IN_PX + ( j + 1 ) * BORDER_SIZE_IN_PX,
								Board::m_Rect.y + i * BOX_SIZE_IN_PX + ( i + 1 ) * BORDER_SIZE_IN_PX,
								BOX_SIZE_IN_PX,
								BOX_SIZE_IN_PX
								};
			m_Board[i][j] = new Box(boxRect, number, correctNumber);
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
	TextureManager::GetInstance()->Draw(BOARD_BKG, Board::m_Rect);
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			m_Board[i][j]->Draw();
		}
	}
}


void Board::HandleEvent(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION || (Board::MouseIsWithin(event.motion.x, event.motion.y) && event.type == SDL_MOUSEBUTTONDOWN))
	{
		bool noBoxIsClicked = true;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (m_Board[i][j]->HandleEvent(event) > -1) {
					m_CurrentBox = m_Board[i][j];
					noBoxIsClicked = false;
				}
			}
		}

		if (noBoxIsClicked) { m_CurrentBox = nullptr; }

	 //Bug khi de xuat cac o cung so
	 
		if (m_CurrentBox != nullptr && m_CurrentBox->GetNumber() > 0) {
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (m_Board[i][j]->GetNumber() == m_CurrentBox->GetNumber())
					{
						m_Board[i][j]->SetHovered(true);
					}
				}
			}
		}

	}
	else if (event.type = SDL_KEYDOWN && m_CurrentBox != nullptr) {
		switch (event.key.keysym.sym)
		{
			case SDLK_1:
				m_CurrentBox->SetNumber(1);
				break;
			case SDLK_2:
				m_CurrentBox->SetNumber(2);
				break;
			case SDLK_3:
				m_CurrentBox->SetNumber(3);
				break;
			case SDLK_4:
				m_CurrentBox->SetNumber(4);
				break;
			case SDLK_5:
				m_CurrentBox->SetNumber(5);
				break;
			case SDLK_6:
				m_CurrentBox->SetNumber(6);
				break;
			case SDLK_7:
				m_CurrentBox->SetNumber(7);
				break;
			case SDLK_8:
				m_CurrentBox->SetNumber(8);
				break;
			case SDLK_9:
				m_CurrentBox->SetNumber(9);
				break;
			case SDLK_BACKSPACE:
			case SDLK_DELETE:
				m_CurrentBox->SetNumber(0);
				break;
			default:
				break;
		}
	}
}