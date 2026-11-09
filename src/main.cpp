#include "raylib.h"
#include <set>
#include <iostream>
#include "../include/global.hpp"
#include "../include/player.hpp"
#include "../include/enemy.hpp"
#include "../include/save.hpp"
#include <vector>
#include <cstdlib>

void DrawBackround()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
                DrawRectangle(starting + (j * backroundSide), starting + (i * backroundSide), backroundSide, backroundSide, RED);
            if (i % 2 == 0 && j % 2 == 1)
            {
                DrawRectangle(starting + (j * backroundSide), starting + (i * backroundSide), backroundSide, backroundSide, BLACK);
            }
            if (i % 2 == 1 && j % 2 == 1)
                DrawRectangle(starting + (j * backroundSide), starting + (i * backroundSide), backroundSide, backroundSide, RED);
            if (i % 2 == 1 && j % 2 == 0)
            {
                DrawRectangle(starting + (j * backroundSide), starting + (i * backroundSide), backroundSide, backroundSide, BLACK);
            }
        }
    }
}

void InitBoard(Board board[][8], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = Empty;
        }
    }

    for (int i = n - 3; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i % 2 == 1 && j % 2 == 0)

                board[i][j] = PlayerPiece;
            if (i % 2 == 0 && j % 2 == 1)
            {
                board[i][j] = PlayerPiece;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i % 2 == 1 && j % 2 == 0)

                board[i][j] = EnemyPiece;
            if (i % 2 == 0 && j % 2 == 1)
            {
                board[i][j] = EnemyPiece;
            }
        }
    }
}

void DrawPieces(Board board[][8], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            switch (board[i][j])
            {
            case Empty:
                break;
            case PlayerPiece:
                DrawRectangle(starting + pieceWidth / 2 + (j * backroundSide), starting + pieceWidth / 2 + (i * backroundSide), pieceWidth, pieceWidth, GREEN);
                break;
            case EnemyPiece:
                DrawRectangle(starting + pieceWidth / 2 + (j * backroundSide), starting + pieceWidth / 2 + (i * backroundSide), pieceWidth, pieceWidth, BLUE);
                break;
            case PlayerKing:
                DrawRectangle(starting + pieceWidth / 2 + (j * backroundSide), starting + pieceWidth / 2 + (i * backroundSide), pieceWidth, pieceWidth, GREEN);
                DrawRectangle(starting + pieceWidth / 1.5f + (j * backroundSide), starting + pieceWidth / 1.5f + (i * backroundSide), pieceWidth / 2, pieceWidth / 2, YELLOW);
                break;
            case EnemyKing:
                DrawRectangle(starting + pieceWidth / 2 + (j * backroundSide), starting + pieceWidth / 2 + (i * backroundSide), pieceWidth, pieceWidth, BLUE);
                DrawRectangle(starting + pieceWidth / 1.5f + (j * backroundSide), starting + pieceWidth / 1.5f + (i * backroundSide), pieceWidth / 2, pieceWidth / 2, YELLOW);
                break;
            }
        }
    }
}

void DrawGameCursor()
{
    const Vector2 mouse = GetMousePosition();
    const Vector2 tip = mouse;
    const Vector2 left = {mouse.x, mouse.y + 20};
    const Vector2 notch = {mouse.x + 5, mouse.y + 15};
    const Vector2 shaftLeft = {mouse.x + 9, mouse.y + 24};
    const Vector2 shaftRight = {mouse.x + 13, mouse.y + 22};
    const Vector2 shoulder = {mouse.x + 9, mouse.y + 13};
    const Vector2 right = {mouse.x + 16, mouse.y + 13};

    DrawTriangle(tip, left, notch, WHITE);
    DrawTriangle(tip, notch, right, WHITE);
    DrawTriangle(notch, shaftLeft, shaftRight, WHITE);
    DrawTriangle(notch, shaftRight, shoulder, WHITE);
    DrawTriangle(notch, shoulder, right, WHITE);

    DrawLineEx(tip, left, 2, BLACK);
    DrawLineEx(left, notch, 2, BLACK);
    DrawLineEx(notch, shaftLeft, 2, BLACK);
    DrawLineEx(shaftLeft, shaftRight, 2, BLACK);
    DrawLineEx(shaftRight, shoulder, 2, BLACK);
    DrawLineEx(shoulder, right, 2, BLACK);
    DrawLineEx(right, tip, 2, BLACK);
}

std::vector<std::tuple<Vector2, Board>> GetEnemyPiecesIndexes(Board board[][8], int n)
{
    std::vector<std::tuple<Vector2, Board>> indexes;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == EnemyPiece || board[i][j] == EnemyKing)
            {
                std::tuple<Vector2, Board> temp{
                    Vector2{static_cast<float>(j), static_cast<float>(i)},
                    board[i][j]};
                indexes.push_back(temp);
            }
        }
    }
    return indexes;
}

std::tuple<std::set<std::pair<int, int>>, int>
GetLongestSet(std::vector<std::set<std::pair<int, int>>> set,
              std::vector<Board> pieceTypeVector)
{
    unsigned length = 0;

    std::vector<
        std::tuple<std::set<std::pair<int, int>>, int>>
        longestPossibleCombos;

    for (unsigned i = 0; i < set.size(); i++)
    {
        unsigned currentLength = set[i].size();

        if (pieceTypeVector[i] == EnemyKing)
        {
            currentLength = static_cast<unsigned>(
                currentLength / 3);
        }

        if (currentLength > length)
        {
            length = currentLength;

            longestPossibleCombos.clear();

            longestPossibleCombos.emplace_back(
                set[i],
                static_cast<int>(i));
        }
        else if (currentLength == length)
        {
            longestPossibleCombos.emplace_back(
                set[i],
                static_cast<int>(i));
        }
    }

    int randomInRange = rand() % longestPossibleCombos.size();

    return longestPossibleCombos[randomInRange];
}

Vector2 GetMoveDestination(Vector2 start, std::set<std::pair<int, int>> theSet)
{
    Vector2 returnVec = start;
    int largest = 0;
    for (auto spot : theSet)
    {
        int distance = std::abs(static_cast<int>(start.x) - spot.first) +
                       std::abs(static_cast<int>(start.y) - spot.second);
        if (distance >= largest)
        {
            largest = distance;
            returnVec = (Vector2){static_cast<float>(spot.first), static_cast<float>(spot.second)};
        }
    }
    return returnVec;
}

std::tuple<bool, int, int> checkForWin(Board board[SIDE][SIDE])
{
    short unsigned playerPieces = 0;
    short unsigned enemyPieces = 0;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == PlayerKing || board[i][j] == PlayerPiece)
                playerPieces++;
            if (board[i][j] == EnemyKing || board[i][j] == EnemyPiece)
                enemyPieces++;
        }
    }
    bool returnBool = !playerPieces || !enemyPieces;
    return {returnBool, playerPieces, enemyPieces};
}

int main()
{
    SavedBoard savedBoard = loadGame();
    Board board[SIDE][SIDE];
    if (!savedBoard.loaded)
    {
        InitBoard(board, SIDE);
    }
    else
    {
        for (int i = 0; i < SIDE; i++)
        {
            for (int j = 0; j < SIDE; j++)
            {
                board[i][j] = savedBoard.board[i][j];
            }
        }
    }

    Vector2 lastPieceOn;

    unsigned turn = 0;

    std::set<std::pair<int, int>> possibleSpotsToMove;

    InitWindow(ScreenSide, ScreenSide, "Checkers");
    HideCursor();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (turn % 2 == 0)
        {
            bool clicked = false;
            player::movePlayer(possibleSpotsToMove, board, lastPieceOn, clicked);
            if (!clicked)
            {
                player::onClickPiece(possibleSpotsToMove, board, lastPieceOn, clicked);
            }
            else
            {
                turn++;
            }
            player::AssignKing(board, SIDE);
        }
        else
        {
            std::vector<std::tuple<Vector2, Board>> pieces = GetEnemyPiecesIndexes(board, SIDE);
            std::vector<std::set<std::pair<int, int>>> set;
            std::vector<Board> pieceTypeVector;
            for (auto piece : pieces)
            {
                std::set<std::pair<int, int>> tempSet;
                enemy::getPossibleMoves(board, std::get<0>(piece), tempSet);
                set.push_back(tempSet);
                pieceTypeVector.push_back(std::get<1>(piece));
            }
            if (!pieces.empty())
            {
                auto [theSet, longestIndex] = GetLongestSet(set, pieceTypeVector);
                if (!theSet.empty())
                {
                    Vector2 chosenPiece = std::get<0>(pieces[longestIndex]);
                    Vector2 chosenDestination = GetMoveDestination(chosenPiece, theSet);
                    enemy::moveEnemy(theSet, board, chosenPiece, chosenDestination);
                }
            }
            turn++;
        }

        BeginDrawing();
        ClearBackground(GRAY);

        DrawBackround();
        DrawPieces(board, SIDE);
        player::DrawMoveRects(possibleSpotsToMove);

        auto [tempCheck, playerPieces, enemyPieces] = checkForWin(board);

        if (IsKeyPressed(KEY_R))
        {
            InitBoard(board, SIDE);
        }

        if (playerPieces == 0)
        {
            const static int font = 40;
            const static int size = MeasureText("You Lost! Press r to restart", font);

            DrawText("You Lost! Press r to restart", ScreenSide / 2 - size / 2, ScreenSide / 2, font, WHITE);
        }

        if (enemyPieces == 0)
        {
            const static int font = 40;
            const static int size = MeasureText("You Won! Press r to restart", font);
            DrawText("You Won! Press r to restart", ScreenSide / 2 - size / 2, ScreenSide / 2, font, WHITE);
        }

        DrawGameCursor();
        EndDrawing();
    }

    CloseWindow();

    SaveGame(board);

    return 0;
}