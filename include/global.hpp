#pragma once
#define ScreenSide 900
#define starting (ScreenSide - 800) / 2
#define pieceWidth 50
#define backroundSide 100
#define SIDE 8

enum Board
{
    Empty,

    PlayerPiece,

    EnemyPiece,

    PlayerKing,

    EnemyKing
};