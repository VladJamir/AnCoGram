#include "board.h"
#include <numeric>
#include <iostream>
/*
 * This function takes the row and column lengths, as well as the clues for each row and column, and prepares the board for solving.
 *
 * @brief Initialize the Board using preprocessing techniques to optimize the solving process.
 * @param rowLength The number of rows in the board.
 * @param columnLength The number of columns in the board.
 * @param rowClues The clues for each row.
 * @param columnClues The clues for each column.
 */
string Board::PreProcessBoard(int rowLength, int columnLength, const vector<vector<int>> rowClues, const vector<vector<int>> columnClues)
{
    string puzzleString(rowLength * columnLength, '.');
    // row processing
    for (int i = 0; i < rowLength; ++i)
    {
        const auto &clue = rowClues[i];
        const int nBlocks = static_cast<int>(clue.size());
        const int rowSum = accumulate(clue.begin(), clue.end(), 0);
        const int rowBase = i * columnLength;

        if (rowSum == columnLength)
        {
            int pos = 0;
            for (int k = 0; k < nBlocks; k++)
            {
                const int block = clue[k];
                for (int j = 0; j < block; j++)
                {
                    puzzleString[rowBase + pos++] = '1';
                }
                if (k + 1 < nBlocks)
                {
                    puzzleString[rowBase + pos++] = '.';
                }
            }
        }
        else if (rowSum + nBlocks - 1 == columnLength)
        {
            int pos = 0;
            for (int k = 0; k < nBlocks; ++k)
            {
                const int block = clue[k];
                for (int j = 0; j < block; j++)
                {
                    puzzleString[rowBase + pos++] = '1';
                }
                if (k + 1 < nBlocks)
                {
                    puzzleString[rowBase + pos++] = '0';
                }
            }
        }
        else
        {
            int sum = 0;
            for (int element : clue)
            {
                int n = columnLength - (nBlocks - 1) - rowSum;
                sum += std::max(0, element - n);
            }
            if (sum > 0)
            {
                cout << "Number of confirmed cells in row " << i << " is greater than 0: " << sum << endl;
                vector<PreprocessingCell> confirmedCells1(columnLength);
                vector<PreprocessingCell> confirmedCells2(columnLength);
                int pos = 0;
                for (int k = 0; k < nBlocks; k++)
                {
                    const int block = clue[k];
                    for (int j = 0; j < block; j++)
                    {
                        confirmedCells1[pos].value = '1';
                        confirmedCells1[pos].blockIndex = k;
                        pos++;
                    }
                    if (k + 1 < nBlocks)
                    {
                        confirmedCells1[pos++].value = '0';
                    }
                }
                pos = 0;
                for (int k = nBlocks - 1; k >= 0; k--)
                {
                    const int block = clue[k];
                    for (int j = 0; j < block; j++)
                    {
                        confirmedCells2[rowLength - 1 - pos].value = '1';
                        confirmedCells2[rowLength - 1 - pos].blockIndex = k;
                        pos++;
                    }
                    if (k > 0)
                    {
                        confirmedCells2[rowLength - 1 - pos++].value = '0';
                    }
                }
                for (int j = 0; j < columnLength; j++)
                {
                    if (confirmedCells1[j].value == "1" && confirmedCells2[j].value == "1" && confirmedCells1[j].blockIndex == confirmedCells2[j].blockIndex)
                    {
                        puzzleString[rowBase + j] = '1';
                    }
                }
            }
        }
    }

    // column processing
    for (int j = 0; j < columnLength; j++)
    {
        const auto &clue = columnClues[j];
        const int nBlocks = static_cast<int>(clue.size());
        const int colSum = accumulate(clue.begin(), clue.end(), 0);

        if (colSum == rowLength)
        {
            int pos = 0;
            for (int k = 0; k < nBlocks; ++k)
            {
                const int block = clue[k];
                for (int i = 0; i < block; i++)
                {
                    puzzleString[pos++ * columnLength + j] = '1';
                }
                if (k + 1 < nBlocks)
                {
                    puzzleString[pos++ * columnLength + j] = '.';
                }
            }
        }
        else if (colSum + nBlocks - 1 == rowLength)
        {
            int pos = 0;
            for (int k = 0; k < nBlocks; ++k)
            {
                const int block = clue[k];
                for (int i = 0; i < block; ++i)
                {
                    puzzleString[pos++ * columnLength + j] = '1';
                }
                if (k + 1 < nBlocks)
                {
                    puzzleString[pos++ * columnLength + j] = '0';
                }
            }
        }
        else
        {
            int sum = 0;
            for (int element : clue)
            {
                int n = rowLength - (nBlocks - 1) - colSum;
                sum += std::max(element - n, 0);
            }
            if (sum > 0)
            {
                cout << "Number of confirmed cells in column " << j << " is greater than 0: " << sum << endl;
                vector<PreprocessingCell> confirmedCells1(rowLength);
                vector<PreprocessingCell> confirmedCells2(rowLength);
                int pos = 0;
                for (int k = 0; k < nBlocks; ++k)
                {
                    const int block = clue[k];
                    for (int i = 0; i < block; i++)
                    {
                        confirmedCells1[pos].value = '1';
                        confirmedCells1[pos].blockIndex = k;
                        pos++;
                    }
                    if (k + 1 < nBlocks)
                    {
                        confirmedCells1[pos].value = '.';
                        confirmedCells1[pos].blockIndex = k;
                        pos++;
                    }
                }
                pos = 0;
                for (int k = nBlocks - 1; k >= 0; k--)
                {
                    const int block = clue[k];
                    for (int i = 0; i < block; i++)
                    {
                        confirmedCells2[columnLength - 1 - pos].value = '1';
                        confirmedCells2[columnLength - 1 - pos].blockIndex = k;
                        pos++;
                    }
                    if (k > 0)
                    {
                        confirmedCells2[columnLength - 1 - pos].value = '.';
                        confirmedCells2[columnLength - 1 - pos].blockIndex = k;
                        pos++;
                    }
                }
                for (int i = 0; i < rowLength; i++)
                {
                    if (confirmedCells1[i].value == "1" && confirmedCells2[i].value == "1" && confirmedCells1[i].blockIndex == confirmedCells2[i].blockIndex)
                    {
                        puzzleString[i * columnLength + j] = '1';
                    }
                }
            }
        }
    }
    return puzzleString;
}