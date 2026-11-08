#include "global.hpp"
#pragma once
struct SavedBoard
{
    Board board[SIDE][SIDE];
    bool loaded = true;
};

void SaveGame(Board board[][SIDE]);

SavedBoard loadGame();

//void ClearSave();