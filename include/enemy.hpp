#include "global.hpp"
#include "raylib.h"
#include <set>
#include <cstdlib>
#include <iostream>
#pragma once
namespace enemy
{
    void findAllSpotsIfPlayer(Board board[][8], int xIndex, int yIndex, std::set<std::pair<int, int>> &possibleSpotsToMove, std::pair<int, int> pieceCoords, std::set<std::pair<int, int>> *visited = nullptr);

    void getPossibleMoves(Board board[][8], Vector2 pieceCoords, std::set<std::pair<int, int>> &possibleSpotsToMove);

    void RemoveCapturedPieces(
        const std::set<std::pair<int, int>> &possibleSpotsToMove,
        Board board[][8],
        const std::pair<int, int> &startPiece,
        const std::pair<int, int> &finalDestination);

    bool moveEnemy(
        const std::set<std::pair<int, int>> &possibleSpotsToMove,
        Board board[][8],
        Vector2 source,
        Vector2 destination);

    void DrawMoveRects(std::set<std::pair<int, int>> &possibleSpotsToMove);

    void AssignKing(Board board[8][8], const int n);
}