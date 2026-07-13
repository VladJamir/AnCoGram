#include <vector>
using namespace std;

class Board
{
public:
    string PreProcessBoard(int rowLength, int columnLength, const vector<vector<int>> rowClues, const vector<vector<int>> columnClues);
    struct PreprocessingCell
    {
        std::string value = ".";
        int blockIndex;
    };
};