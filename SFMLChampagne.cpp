#include <iostream>
#include <crtdbg.h>

#include "Game.h"
#include "LevelState.h"

using namespace std;

LevelState* LevelState::mInstance = nullptr;
Game* Game::mInstance = nullptr;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);           // Check if there are 
                                                                            // some memory leak
    Game* game = Game::GetInstance();
    LevelState* level = LevelState::GetInstance();
    game->AddState(level);

    game->LaunchGame();

    delete game;
    return 0;
}