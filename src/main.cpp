#include "arguments.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "board.h"

using namespace std;

void ReadFile(string filename, int &rowLength, int &columnLength, vector<vector<int>> &rowClues, vector<vector<int>> &columnClues)
{
    ifstream file;
    file.open(filename);

    if (file.is_open())
    {
        string r, c;
        std::getline(file, r);
        std::getline(file, c);
        rowLength = stoi(r);
        columnLength = stoi(c);
        rowClues.assign(rowLength, vector<int>());
        columnClues.assign(columnLength, vector<int>());
        string tempRowClue;
        for (int i = 0; i < rowLength; i++)
        {
            std::getline(file, tempRowClue);
            std::istringstream iss(tempRowClue);
            stringstream ss(tempRowClue);
            int num;
            while (ss >> num)
            {
                rowClues[i].push_back(num);
            }
        }
        string tempColumnClue;
        for (int i = 0; i < columnLength; i++)
        {
            std::getline(file, tempColumnClue);
            std::istringstream iss(tempColumnClue);
            stringstream ss(tempColumnClue);
            int num;
            while (ss >> num)
            {
                columnClues[i].push_back(num);
            }
        }
        file.close();
        cout << "Row Length: " << rowLength << endl;
        for (const auto &row : rowClues)
        {
            for (int clue : row)
            {
                cout << clue << " ";
            }
            cout << endl;
        }
        cout << "Column Length: " << columnLength << endl;
        for (const auto &column : columnClues)
        {
            for (int clue : column)
            {
                cout << clue << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cerr << "Unable to open file: " << filename << endl;
    }
}

int main(int argc, char *argv[])
{
    Arguments a(argc, argv);

    int rowLength = 0;
    int columnLength = 0;
    vector<vector<int>> rowClues;
    vector<vector<int>> columnClues;

    string puzzleFile = a.GetArg<string>("file", "");

    ReadFile(puzzleFile, rowLength, columnLength, rowClues, columnClues);

    string puzzleString = string(rowLength * columnLength, '.');

    bool preprocess = a.GetArg<bool>("preprocess", true);

    if (preprocess)
    {
        Board board;
        puzzleString = board.PreProcessBoard(rowLength, columnLength, rowClues, columnClues);
    }
    cout << "Puzzle String: " << puzzleString << endl;
    return 0;
}