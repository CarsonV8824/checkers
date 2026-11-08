#include "raylib.h"
#include <set>
#include <iostream>
#include "../include/global.hpp"
#include "../include/player.hpp"
#include "../include/enemy.hpp"
#include "../include/save.hpp"
#include <vector>

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
                DrawRectangle(starting + pieceWidth / 2 + (j * backroundSide), starting + pieceWidth / 2 + (i * backroundSide), pieceWidth, pieceWidth, PURPLE);
                break;
            case EnemyKing:
                DrawRectangle(starting + pieceWidth / 2 + (j * backroundSide), starting + pieceWidth / 2 + (i * backroundSide), pieceWidth, pieceWidth, ORANGE);
                break;
            }
        }
    }
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

std::tuple<std::set<std::pair<int, int>>, int> GetLongestSet(std::vector<std::set<std::pair<int, int>>> set, std::vector<Board> pieceTypeVector)
{
    unsigned length = 0;
    int index = 0;
    std::set<std::pair<int, int>> longest;
    for (unsigned i = 0; i < set.size(); i++)
    {
        if (pieceTypeVector[i] == EnemyPiece)
        {

            if (set[i].size() >= length)
            {
                length = set[i].size();
                longest = set[i];
                index = static_cast<int>(i);
            }
        }
        else if (pieceTypeVector[i] == EnemyKing)
        {
            if (set[i].size() / 2 >= length)
            {
                length = set[i].size();
                longest = set[i];
                index = static_cast<int>(i);
            }
        }
    }
    return {longest, index};
}

Vector2 GetMoveDestination(Vector2 start, std::set<std::pair<int, int>> theSet)
{
    Vector2 returnVec = start;
    int largest = 0;
    for (auto spot : theSet)
    {
        int distance = std::abs(static_cast<int>(start.x) - spot.first) +
                       std::abs(static_cast<int>(start.y) - spot.second);
        if (distance > largest)
        {
            largest = distance;
            returnVec = (Vector2){static_cast<float>(spot.first), static_cast<float>(spot.second)};
        }
    }
    return returnVec;
}

bool checkForWin(Board board[SIDE][SIDE])
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
    return returnBool;
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

    InitWindow(ScreenSide, ScreenSide, "raylib [core] example - basic window");

    SetTargetFPS(60);
    bool endCondition = false;
    bool resetKeyPressed = false;
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

        EndDrawing();

        endCondition = checkForWin(board);
        if (IsKeyPressed(KEY_R))
        {
            resetKeyPressed = true;
            InitBoard(board, SIDE);
        }
    }

    CloseWindow();
    if (!endCondition)
        SaveGame(board);
    if (endCondition)
        ClearSave();
    if (resetKeyPressed)
        ClearSave();
    return 0;
}