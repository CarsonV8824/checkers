#include "raylib.h"
#include <set>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include "../include/global.hpp"

namespace player
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

        if (yIndex > 0)
        {
            if (xIndex > 0)
            {
                std::pair<int, int> temp;
                temp.first = xIndex - 1;
                temp.second = yIndex - 1;
                if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
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
                if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
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
        if (board[pieceCoords.second][pieceCoords.first] == PlayerKing && yIndex < SIDE - 1)
        {
            if (xIndex > 0)
            {
                std::pair<int, int> temp;
                temp.first = xIndex - 1;
                temp.second = yIndex + 1;
                if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
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
                if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
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
    }

    void onClickPiece(std::set<std::pair<int, int>> &possibleSpotsToMove, Board board[][8], Vector2 &mouseCoords, bool &clicked)
    {
        int xIndex = 0;
        int yIndex = 0;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mouseCoords = {0, 0};
            mouseCoords = GetMousePosition();
            xIndex = ((int)mouseCoords.x - starting) / backroundSide;
            yIndex = ((int)mouseCoords.y - starting) / backroundSide;

            if (xIndex < 0 || xIndex >= SIDE || yIndex < 0 || yIndex >= SIDE)
                return;

            if (board[yIndex][xIndex] == PlayerPiece || board[yIndex][xIndex] == PlayerKing)
            {
                possibleSpotsToMove.clear();

                if (yIndex > 0)
                {
                    if (xIndex > 0)
                    {
                        std::pair<int, int> temp;
                        temp.first = xIndex - 1;
                        temp.second = yIndex - 1;
                        if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
                        {
                            findAllSpotsIfEnemy(board, temp.first - 1, temp.second - 1, possibleSpotsToMove, {xIndex, yIndex});
                        }

                        if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                            possibleSpotsToMove.insert(temp);
                    }
                    if (xIndex < SIDE - 1)
                    {
                        std::pair<int, int> temp;
                        temp.first = xIndex + 1;
                        temp.second = yIndex - 1;
                        if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
                        {
                            findAllSpotsIfEnemy(board, temp.first + 1, temp.second - 1, possibleSpotsToMove, {xIndex, yIndex});
                        }
                        if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                            possibleSpotsToMove.insert(temp);
                    }
                }
                if (board[yIndex][xIndex] == PlayerKing && yIndex < SIDE - 1)
                {
                    if (xIndex > 0)
                    {
                        std::pair<int, int> temp;
                        temp.first = xIndex - 1;
                        temp.second = yIndex + 1;
                        if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
                        {
                            findAllSpotsIfEnemy(board, temp.first - 1, temp.second + 1, possibleSpotsToMove, {xIndex, yIndex});
                        }

                        if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                            possibleSpotsToMove.insert(temp);
                    }
                    if (xIndex < SIDE - 1)
                    {
                        std::pair<int, int> temp;
                        temp.first = xIndex + 1;
                        temp.second = yIndex + 1;
                        if (board[temp.second][temp.first] == EnemyKing || board[temp.second][temp.first] == EnemyPiece)
                        {
                            findAllSpotsIfEnemy(board, temp.first + 1, temp.second + 1, possibleSpotsToMove, {xIndex, yIndex});
                        }
                        if (board[temp.second][temp.first] != PlayerKing && board[temp.second][temp.first] != PlayerPiece && board[temp.second][temp.first] != EnemyPiece && board[temp.second][temp.first] != EnemyKing)
                            possibleSpotsToMove.insert(temp);
                    }
                }
                clicked = true;
            }
            else
            {
                possibleSpotsToMove.clear();
            }
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

                const int enemyX = (spot.first + current.first) / 2;
                const int enemyY = (spot.second + current.second) / 2;
                if (board[enemyY][enemyX] != EnemyPiece &&
                    board[enemyY][enemyX] != EnemyKing)
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
            const int enemyX = (current.first + prior.first) / 2;
            const int enemyY = (current.second + prior.second) / 2;
            board[enemyY][enemyX] = Empty;
            current = prior;
        }
    }

    void movePlayer(
        std::set<std::pair<int, int>> &possibleSpotsToMove,
        Board board[][8],
        Vector2 &mouseCoords,
        bool &clicked)
    {
        static int selectedX = -1;
        static int selectedY = -1;
        static Board selectedPiece = Empty;
        static bool pieceSelected = false;

        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return;

        mouseCoords = GetMousePosition();

        int xIndex = ((int)mouseCoords.x - starting) / backroundSide;
        int yIndex = ((int)mouseCoords.y - starting) / backroundSide;

        if (xIndex < 0 || xIndex >= 8 ||
            yIndex < 0 || yIndex >= 8)
        {
            return;
        }

        // Select a piece
        if (!pieceSelected)
        {
            if (board[yIndex][xIndex] != PlayerPiece && board[yIndex][xIndex] != PlayerKing)
                return;

            selectedPiece = board[yIndex][xIndex];
            selectedX = xIndex;
            selectedY = yIndex;
            pieceSelected = true;

            return;
        }

        std::pair<int, int> destination = {xIndex, yIndex};

        // Perform move
        if (possibleSpotsToMove.find(destination) != possibleSpotsToMove.end())
        {
            std::pair<int, int> startPiece =
                {
                    selectedX,
                    selectedY};

            RemoveCapturedPieces(
                possibleSpotsToMove,
                board,
                startPiece,
                destination);

            board[destination.second][destination.first] = selectedPiece;
            board[selectedY][selectedX] = Empty;

            pieceSelected = false;
            possibleSpotsToMove.clear();
            clicked = true;
        }
        // Select another piece
        else if (board[yIndex][xIndex] == PlayerPiece || board[yIndex][xIndex] == PlayerKing)
        {
            selectedPiece = board[yIndex][xIndex];
            selectedX = xIndex;
            selectedY = yIndex;
        }
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
            if (board[0][i] == PlayerPiece)
            {
                board[0][i] = PlayerKing;
            }
        }
    }
}