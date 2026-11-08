#include "raylib.h"
#include <set>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include "../include/global.hpp"

namespace enemy
{
    void findAllSpotsIfEnemy(Board board[][8], int xIndex, int yIndex, std::set<std::pair<int, int>> &possibleSpotsToMove, std::pair<int, int> pieceCoords, std::set<std::pair<int, int>> *visited = nullptr)
    {
        std::set<std::pair<int, int>> localVisited;
        if (visited == nullptr)
            visited = &localVisited;

        if (xIndex < 0 || xIndex >= SIDE || yIndex < 0 || yIndex >= SIDE)
            return;
        if (board[yIndex][xIndex] != Empty || !visited->insert({xIndex, yIndex}).second)
            return;

        if (board[yIndex][xIndex] == Empty)
        {
            std::pair<int, int> temp;
            temp.first = xIndex;
            temp.second = yIndex;
            bool check = possibleSpotsToMove.find({xIndex, yIndex}) != possibleSpotsToMove.end();
            bool firstExists = possibleSpotsToMove.find({xIndex - 1, yIndex - 1}) != possibleSpotsToMove.end();
            bool secondExists = possibleSpotsToMove.find({xIndex - 1, yIndex + 1}) != possibleSpotsToMove.end();
            bool thirdExists = possibleSpotsToMove.find({xIndex + 1, yIndex - 1}) != possibleSpotsToMove.end();
            bool forthExists = possibleSpotsToMove.find({xIndex + 1, yIndex + 1}) != possibleSpotsToMove.end();
            if (!firstExists && !secondExists && !thirdExists && !forthExists && !check)
            {
                possibleSpotsToMove.insert(temp);
            }
        }

        if (yIndex < SIDE - 1)
        {
            if (xIndex > 0)
            {
                std::pair<int, int> temp;
                temp.first = xIndex - 1;
                temp.second = yIndex + 1;
                if (board[temp.second][temp.first] == PlayerKing || board[temp.second][temp.first] == PlayerPiece)
                {
                    findAllSpotsIfEnemy(board, temp.first - 1, temp.second + 1, possibleSpotsToMove, pieceCoords, visited);
                }

                if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                {
                    bool check = possibleSpotsToMove.find({temp.first, temp.second}) != possibleSpotsToMove.end();
                    bool firstExists = possibleSpotsToMove.find({temp.first - 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool secondExists = possibleSpotsToMove.find({temp.first - 1, temp.second + 1}) != possibleSpotsToMove.end();
                    bool thirdExists = possibleSpotsToMove.find({temp.first + 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool forthExists = possibleSpotsToMove.find({temp.first + 1, temp.second + 1}) != possibleSpotsToMove.end();
                    if (!firstExists && !secondExists && !thirdExists && !forthExists && !check)
                        possibleSpotsToMove.insert(temp);
                }
            }
            if (xIndex < SIDE - 1)
            {
                std::pair<int, int> temp;
                temp.first = xIndex + 1;
                temp.second = yIndex + 1;
                if (board[temp.second][temp.first] == PlayerKing || board[temp.second][temp.first] == PlayerPiece)
                {
                    findAllSpotsIfEnemy(board, temp.first + 1, temp.second + 1, possibleSpotsToMove, pieceCoords, visited);
                }
                if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                {
                    bool check = possibleSpotsToMove.find({temp.first, temp.second}) != possibleSpotsToMove.end();
                    bool firstExists = possibleSpotsToMove.find({temp.first - 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool secondExists = possibleSpotsToMove.find({temp.first - 1, temp.second + 1}) != possibleSpotsToMove.end();
                    bool thirdExists = possibleSpotsToMove.find({temp.first + 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool forthExists = possibleSpotsToMove.find({temp.first + 1, temp.second + 1}) != possibleSpotsToMove.end();
                    if (!firstExists && !secondExists && !thirdExists && !forthExists && !check)
                        possibleSpotsToMove.insert(temp);
                }
            }
        }
        if (board[pieceCoords.second][pieceCoords.first] == EnemyKing && yIndex > 0)
        {
            if (xIndex > 0)
            {
                std::pair<int, int> temp;
                temp.first = xIndex - 1;
                temp.second = yIndex - 1;
                if (board[temp.second][temp.first] == PlayerKing || board[temp.second][temp.first] == PlayerPiece)
                {
                    findAllSpotsIfEnemy(board, temp.first - 1, temp.second - 1, possibleSpotsToMove, pieceCoords, visited);
                }

                if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                {
                    bool check = possibleSpotsToMove.find({temp.first, temp.second}) != possibleSpotsToMove.end();
                    bool firstExists = possibleSpotsToMove.find({temp.first - 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool secondExists = possibleSpotsToMove.find({temp.first - 1, temp.second + 1}) != possibleSpotsToMove.end();
                    bool thirdExists = possibleSpotsToMove.find({temp.first + 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool forthExists = possibleSpotsToMove.find({temp.first + 1, temp.second + 1}) != possibleSpotsToMove.end();
                    if (!firstExists && !secondExists && !thirdExists && !forthExists && !check)
                        possibleSpotsToMove.insert(temp);
                }
            }
            if (xIndex < SIDE - 1)
            {
                std::pair<int, int> temp;
                temp.first = xIndex + 1;
                temp.second = yIndex - 1;
                if (board[temp.second][temp.first] == PlayerKing || board[temp.second][temp.first] == PlayerPiece)
                {
                    findAllSpotsIfEnemy(board, temp.first + 1, temp.second - 1, possibleSpotsToMove, pieceCoords, visited);
                }
                if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                {
                    bool check = possibleSpotsToMove.find({temp.first, temp.second}) != possibleSpotsToMove.end();
                    bool firstExists = possibleSpotsToMove.find({temp.first - 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool secondExists = possibleSpotsToMove.find({temp.first - 1, temp.second + 1}) != possibleSpotsToMove.end();
                    bool thirdExists = possibleSpotsToMove.find({temp.first + 1, temp.second - 1}) != possibleSpotsToMove.end();
                    bool forthExists = possibleSpotsToMove.find({temp.first + 1, temp.second + 1}) != possibleSpotsToMove.end();
                    if (!firstExists && !secondExists && !thirdExists && !forthExists && !check)
                        possibleSpotsToMove.insert(temp);
                }
            }
        }
    }

    void getPossibleMoves(Board board[][8], Vector2 pieceCoords, std::set<std::pair<int, int>> &possibleSpotsToMove)
    {
        possibleSpotsToMove.clear();
        const int xIndex = static_cast<int>(pieceCoords.x);
        const int yIndex = static_cast<int>(pieceCoords.y);

        if (xIndex < 0 || xIndex >= SIDE || yIndex < 0 || yIndex >= SIDE)
            return;

        const Board piece = board[yIndex][xIndex];
        if (piece != EnemyPiece && piece != EnemyKing)
            return;

        const int directionCount = piece == EnemyKing ? 4 : 2;
        const int directions[4][2] = {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}};

        for (int i = 0; i < directionCount; ++i)
        {
            const int dx = directions[i][0];
            const int dy = directions[i][1];
            const int adjacentX = xIndex + dx;
            const int adjacentY = yIndex + dy;

            if (adjacentX < 0 || adjacentX >= SIDE || adjacentY < 0 || adjacentY >= SIDE)
                continue;

            if (board[adjacentY][adjacentX] == Empty)
            {
                possibleSpotsToMove.insert({adjacentX, adjacentY});
                continue;
            }

            const int landingX = xIndex + dx * 2;
            const int landingY = yIndex + dy * 2;
            const Board adjacentPiece = board[adjacentY][adjacentX];
            if ((adjacentPiece != PlayerPiece && adjacentPiece != PlayerKing) ||
                landingX < 0 || landingX >= SIDE || landingY < 0 || landingY >= SIDE ||
                board[landingY][landingX] != Empty)
            {
                continue;
            }

            possibleSpotsToMove.insert({landingX, landingY});
            findAllSpotsIfEnemy(board, landingX, landingY, possibleSpotsToMove, {xIndex, yIndex});
        }
    }

    // this function made me give up!
    void RemoveCapturedPieces(
        const std::set<std::pair<int, int>> &possibleSpotsToMove,
        Board board[][8],
        const std::pair<int, int> &startPiece,
        const std::pair<int, int> &finalDestination)
    {
        if (startPiece.first < 0 || startPiece.first >= SIDE ||
            startPiece.second < 0 || startPiece.second >= SIDE ||
            finalDestination.first < 0 || finalDestination.first >= SIDE ||
            finalDestination.second < 0 || finalDestination.second >= SIDE)
        {
            std::cerr << "Cannot reconstruct capture path for out-of-bounds coordinates\n";
            return;
        }

        using Coordinates = std::pair<int, int>;
        std::queue<Coordinates> pending;
        std::map<Coordinates, Coordinates> previous;
        pending.push(startPiece);
        previous.emplace(startPiece, startPiece);

        while (!pending.empty() && previous.find(finalDestination) == previous.end())
        {
            const Coordinates current = pending.front();
            pending.pop();

            for (const Coordinates &spot : possibleSpotsToMove)
            {
                const int dx = spot.first - current.first;
                const int dy = spot.second - current.second;
                if (spot.first < 0 || spot.first >= SIDE ||
                    spot.second < 0 || spot.second >= SIDE ||
                    std::abs(dx) != 2 || std::abs(dy) != 2 ||
                    previous.find(spot) != previous.end())
                {
                    continue;
                }

                const int capturedX = (spot.first + current.first) / 2;
                const int capturedY = (spot.second + current.second) / 2;
                if (board[capturedY][capturedX] != PlayerPiece &&
                    board[capturedY][capturedX] != PlayerKing)
                {
                    continue;
                }

                previous.emplace(spot, current);
                pending.push(spot);
            }
        }

        if (previous.find(finalDestination) == previous.end())
            return;

        Coordinates current = finalDestination;
        while (current != startPiece)
        {
            const Coordinates prior = previous.at(current);
            const int capturedX = (current.first + prior.first) / 2;
            const int capturedY = (current.second + prior.second) / 2;
            board[capturedY][capturedX] = Empty;
            current = prior;
        }
    }

    bool moveEnemy(
        const std::set<std::pair<int, int>> &possibleSpotsToMove,
        Board board[][8],
        Vector2 source,
        Vector2 destination)
    {
        const int sourceX = static_cast<int>(source.x);
        const int sourceY = static_cast<int>(source.y);
        const int destinationX = static_cast<int>(destination.x);
        const int destinationY = static_cast<int>(destination.y);

        if (sourceX < 0 || sourceX >= SIDE || sourceY < 0 || sourceY >= SIDE ||
            destinationX < 0 || destinationX >= SIDE || destinationY < 0 || destinationY >= SIDE ||
            !possibleSpotsToMove.count({destinationX, destinationY}))
        {
            return false;
        }

        const Board piece = board[sourceY][sourceX];
        if (piece != EnemyPiece && piece != EnemyKing)
            return false;

        const std::pair<int, int> start = {sourceX, sourceY};
        const std::pair<int, int> end = {destinationX, destinationY};
        RemoveCapturedPieces(possibleSpotsToMove, board, start, end);
        board[sourceY][sourceX] = Empty;
        board[destinationY][destinationX] = piece;
        if (piece == EnemyPiece && destinationY == SIDE - 1)
            board[destinationY][destinationX] = EnemyKing;
        return true;
    }

    void DrawMoveRects(std::set<std::pair<int, int>> &possibleSpotsToMove)
    {
        if (!possibleSpotsToMove.empty())
        {
            for (auto possible : possibleSpotsToMove)
            {
                DrawRectangle((possible.first * backroundSide) + starting, (possible.second * backroundSide) + starting, 100, 100, (Color){0, 255, 0, 100});
                // std::cout << possible.first << " " << possible.second << "\n";
            }
        }
    }

    void AssignKing(Board board[8][8], const int n)
    {
        for (int i = 0; i < n; i++)
        {
            if (board[SIDE - 1][i] == EnemyPiece)
            {
                board[SIDE - 1][i] = EnemyKing;
            }
        }
    }
}