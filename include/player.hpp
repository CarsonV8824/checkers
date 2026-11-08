#pragma once
namespace player
{
    void findAllSpotsIfEnemy(Board board[][8], int xIndex, int yIndex, std::set<std::pair<int, int>> &possibleSpotsToMove, std::pair<int, int> pieceCoords, std::set<std::pair<int, int>> *visited = nullptr);

    void onClickPiece(std::set<std::pair<int, int>> &possibleSpotsToMove, Board board[][8], Vector2 &mouseCoords, bool &clicked);

    void RemoveCapturedPieces(
        const std::set<std::pair<int, int>> &possibleSpotsToMove,
        Board board[][8],
        const std::pair<int, int> &startPiece,
        const std::pair<int, int> &finalDestination);

    void movePlayer(
        std::set<std::pair<int, int>> &possibleSpotsToMove,
        Board board[][8],
        Vector2 &mouseCoords,
        bool &clicked);

    void DrawMoveRects(std::set<std::pair<int, int>> &possibleSpotsToMove);

    void AssignKing(Board board[8][8], const int n);
}