#include "../include/global.hpp"
#include <fstream>
#include <cstdlib>

struct SavedBoard
{
    Board board[SIDE][SIDE] = {{}};
    bool loaded = true;
};

void SaveGame(Board board[][SIDE])
{
    std::ofstream saveToFile("save.txt");
    if (!saveToFile)
    {
        exit(EXIT_FAILURE);
        printf("Error opening save.txt");
    }
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            saveToFile << board[i][j] << " ";
        }
        saveToFile << "\n";
    }
    saveToFile.close();
}

SavedBoard loadGame()
{
    std::ifstream loadFromFile("save.txt");

    SavedBoard returnBoard;

    if (!loadFromFile)
    {
        printf("Error opening save.txt\n");
        returnBoard.loaded = false;
        loadFromFile.close();
        return returnBoard;
    }

    if (loadFromFile.peek() == std::ifstream::traits_type::eof())
    {
        printf("File is empty\n");
        returnBoard.loaded = false;
        loadFromFile.close();
        return returnBoard;
    }

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int value;

            if (!(loadFromFile >> value))
            {
                printf("Save file is corrupted\n");
                returnBoard.loaded = false;
                return returnBoard;
            }
            printf("%d\n", value);
            returnBoard.board[row][col] = (Board)value;
        }
    }
    loadFromFile.close();
    return returnBoard;
}

/*void ClearSave()
{
    std::ofstream file("save.txt", std::ios::trunc);
    if (!file)
        exit(EXIT_FAILURE);
    file.close();
}*/