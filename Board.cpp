
#include "Board.h"
#include <random>
#include "TextureManager.h"
#include "EventHandler.h"


bool Board::Init(LEVEL level)
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
			if (number < 0 || number > 9 ||	correctNumber < 0 || correctNumber > 9)
			{
				printf("Incorrect data at position %ld of file %s\n", ftell(fptr), filepath.c_str());
				fclose(fptr);
				fptr = nullptr;
				return false;
			}
			SDL_Rect boxRect = { m_Rect.x + BoardAssets[j], m_Rect.y + BoardAssets[i], BOX_SIZE_IN_PX, BOX_SIZE_IN_PX};
			m_Board[i][j] = new Box(boxRect, MOUSE_DOWN_COLOR, MOUSE_HOVERING_COLOR, number, correctNumber);
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
	TextureManager::GetInstance()->Draw("board", Board::m_Rect);
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			m_Board[i][j]->Draw();
		}
	}
}


void Board::HandleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION || (Board::MouseIsWithin(event.motion.x, event.motion.y) && event.type == SDL_MOUSEBUTTONDOWN))
	{
		bool noBoxIsClicked = true;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (m_Board[i][j]->HandleEvent(event) > -1) {
					m_CurrRow = i;
					m_CurrCol = j;
					noBoxIsClicked = false;
				}
			}
		}

		if (noBoxIsClicked) {
			m_CurrRow = m_CurrCol = UNDEFINED;
		}
	}
	SuggestRelatedCells();
}

void Board::HandleKeyboard(SDL_Event& event, Pencil* pencil)
{
	// chuc nang da ok nhung can xu ly gon hon
	if( m_CurrRow != UNDEFINED && m_CurrCol != UNDEFINED) {
		if(event.type == SDL_KEYDOWN && !EventHandler::GetInstance()->m_KeyClicked) {
			EventHandler::GetInstance()->m_KeyClicked = true;
			SDL_Keycode keycode = event.key.keysym.sym;
			if (SDLK_1 <= keycode && keycode <= SDLK_9) {
				if (pencil->IsSelected()) {
					m_Board[m_CurrRow][m_CurrCol]->SetDraftNumber(keycode - SDLK_0);
				}
				else if (!m_Board[m_CurrRow][m_CurrCol]->SetNumber(keycode - SDLK_0)) {
					m_WrongTimesLeft--;
				}
			}
			else if (keycode == SDLK_DELETE || keycode == SDLK_BACKSPACE) {
				if (pencil->IsSelected()) {
					m_Board[m_CurrRow][m_CurrCol]->SetDraftNumber(0);
				}
				else if (!m_Board[m_CurrRow][m_CurrCol]->SetNumber(0)) {
					m_WrongTimesLeft--;
				}
			}

		}
		else if (event.type == SDL_KEYUP) {
			EventHandler::GetInstance()->m_KeyClicked = false;
		}
	}
}

// Suggest related cells
void Board::SuggestRelatedCells()
{
	if ( m_CurrRow != UNDEFINED && m_CurrCol != UNDEFINED ) {
		if (m_Board[m_CurrRow][m_CurrCol]->IsSelected()) {
			// Suggest same numbers
			int currentNumber = m_Board[m_CurrRow][m_CurrCol]->GetHoldingNumber();
			if (currentNumber > 0) {
				for (int i = 0; i < BOARD_SIZE; i++) {
					for (int j = 0; j < BOARD_SIZE; j++) {
						if (m_Board[i][j]->GetHoldingNumber() == m_Board[m_CurrRow][m_CurrCol]->GetHoldingNumber()) {
							m_Board[i][j]->SetColor(MOUSE_DOWN_COLOR);
						}
					}
				}
			}

			// Suggest row and column
			for (int i = 0; i < BOARD_SIZE; i++) {
				m_Board[i][m_CurrCol]->SetColor(MOUSE_HOVERING_COLOR);
				m_Board[m_CurrRow][i]->SetColor(MOUSE_HOVERING_COLOR);
			}

			// Suggest 3x3 block
			int blockX = (m_CurrRow / 3) * 3;
			int blockY = (m_CurrCol / 3) * 3;
			for (int i = blockX; i < blockX + 3; i++) {
				for (int j = blockY; j < blockY + 3; j++) {
					m_Board[i][j]->SetColor(MOUSE_HOVERING_COLOR);
				}
			}
			m_Board[m_CurrRow][m_CurrCol]->SetColor(MOUSE_DOWN_COLOR);
		}
	}
}

bool Board::IsCompleted()
{
	int countCorrectBoxes = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			countCorrectBoxes += m_Board[i][j]->IsCorrect();
		}
	}
	return countCorrectBoxes >= 81;
}
