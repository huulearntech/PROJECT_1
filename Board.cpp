#include "Game.h"
#include "TextureManager.h"
#include "Board.h"
#include <random>


bool Board::Init(LEVEL level)
{
	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), BOARD_BKG.r, BOARD_BKG.g, BOARD_BKG.b, BOARD_BKG.a);
	SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &m_Rect);

	if (Board::LoadData(level) == false) { return false; }
	Board::Draw();

	return true;
}

bool Board::LoadData(LEVEL level)
{
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

	FILE* fptr;
	if (fopen_s(&fptr,filepath.c_str(), "r") != 0) {
		printf("Failed in loading board data: Can't open file %s\n", filepath.c_str());
		return false;
	}
	int offset = (rand() % NUMBER_OF_RECORDS) * RECORD_SIZE;
	fseek(fptr, offset, SEEK_SET);

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			int number = fgetc(fptr) - '0';
			int correctNumber = fgetc(fptr) - '0';
			if (number != correctNumber ||
				number < 0 || number > 9 ||
				correctNumber < 0 || correctNumber > 9)
			{
				printf("Incorrect data at position %ld of file %s\n", ftell(fptr), filepath.c_str());
				fclose(fptr);
				fptr = nullptr;
				return false;
			}
			SDL_Rect boxRect = {i * BOX_SIZE_IN_PX + ( i + 1 ) * BORDER_SIZE_IN_PX,
								j * BOX_SIZE_IN_PX + ( j + 1 ) * BORDER_SIZE_IN_PX,
								BOX_SIZE_IN_PX,
								BOX_SIZE_IN_PX
								};
			//to do
			m_Board[i][j] = new Box(boxRect, number, correctNumber);
		}
	}

	fclose(fptr);
	fptr = nullptr;

	return true;
}



void Board::Draw()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			m_Board[i][j]->Draw();
		}
	}
}



void Board::Update(SDL_Event event) const
{
	int mouseX = event.motion.x, mouseY = event.motion.y;
	if (!Board::MouseIsWithin(mouseX, mouseY)) { return; }
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (m_Board[i][j]->MouseIsWithin(mouseX, mouseY))
			{
				m_Board[i][j]->HandleEvent(event);
			}
		}
	}
}