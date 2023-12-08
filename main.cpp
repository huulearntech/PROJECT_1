#include "Game.h"

int main(int argc, char** argv) {
	Game::GetInstance()->Init();
	Game::GetInstance()->Play();
	Game::GetInstance()->Clean();
	return 0;
}