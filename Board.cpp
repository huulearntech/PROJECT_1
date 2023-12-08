#include "Board.h"
#include "TextureManager.h"
#include "Game.h"
#include <random>




bool Board::Init(LEVEL level)
{
	TextureManager::GetInstance()->Load("board", "SudokuBKG.png");

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
		filepath = EASY_FILE_PATH;
		break;
	case LEVEL::MEDIUM:
		filepath = MEDIUM_FILE_PATH;
		break;
	case LEVEL::HARD:
		filepath = HARD_FILE_PATH;
		break;
	case LEVEL::EXTREME:
		filepath = EXTREME_FILE_PATH;
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
			std::string textureID = "" + number;
			SDL_Rect boxRect = {i * BOX_SIZE_IN_PX + ( i + 1 ) * BORDER_SIZE_IN_PX,
								j * BOX_SIZE_IN_PX + ( j + 1 ) * BORDER_SIZE_IN_PX,
								BOX_SIZE_IN_PX,
								BOX_SIZE_IN_PX
								};
			m_Board[i][j] = new Box(textureID, boxRect, number, correctNumber);
		}
	}

	fclose(fptr);
	fptr = nullptr;

	return true;
}



void Board::Draw()
{
	TextureManager::GetInstance()->Draw("board", Board::GetRect());
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			m_Board[i][j]->Draw();
		}
	}
}



void Board::Update(const int& mouseX, const int& mouseY) const
{
	if (!Board::MouseIsWithin(mouseX, mouseY)) { return; }

}