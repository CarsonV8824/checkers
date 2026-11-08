#include "raylib.h"
#include <set>
#include <iostream>
#include "../include/global.hpp"
#include "../include/player.hpp"
#include "../include/enemy.hpp"
#include <vector>
#include <cstddef>

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
            if (i % 2 == 1 && j % 2 == 0 && i != 1)

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

std::vector<Vector2> GetEnemyPiecesIndexes(Board board[][8], int n)
{
    std::vector<Vector2> indexes;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == EnemyPiece || board[i][j] == EnemyKing)
            {
                indexes.push_back((Vector2){static_cast<float>(j), static_cast<float>(i)});
            }
        }
    }
    return indexes;
}

std::tuple<std::set<std::pair<int, int>>, int> GetLongestSet(std::vector<std::set<std::pair<int, int>>> set)
{
    std::size_t length = 0;
    int index = 0;
    std::set<std::pair<int, int>> longest;
    for (std::size_t i = 0; i < set.size(); i++)
    {
        if (set[i].size() > length)
        {
            length = set[i].size();
            longest = set[i];
            index = static_cast<int>(i);
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

int main()
{
    Board board[SIDE][SIDE];
    InitBoard(board, SIDE);
    Vector2 lastPieceOn;

    unsigned turn = 0;

    std::set<std::pair<int, int>> possibleSpotsToMove;

    InitWindow(ScreenSide, ScreenSide, "raylib [core] example - basic window");

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
            std::vector<Vector2> pieces = GetEnemyPiecesIndexes(board, SIDE);
            std::vector<std::set<std::pair<int, int>>> set;
            for (auto piece : pieces)
            {
                std::set<std::pair<int, int>> tempSet;
                enemy::getPossibleMoves(board, piece, tempSet);
                set.push_back(tempSet);
            }
            if (!pieces.empty())
            {
                auto [theSet, longestIndex] = GetLongestSet(set);
                if (!theSet.empty())
                {
                    Vector2 chosenPiece = pieces[longestIndex];
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
    }

    CloseWindow();

    return 0;
}