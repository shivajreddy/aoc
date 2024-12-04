#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#pragma region using-statments
using std::cerr;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;
#pragma endregion

#pragma region Program-Constants
const string FILE_PATH = "./2024/cpp/day-04/part-01/test.txt";
// const string FILE_PATH = "./2024/cpp/day-04/part-01/input.txt";
#pragma endregion

/*

Goal of the problem
- For every

*/

// Helper Fn
void printVector(vector<char> vec)
{
    for (auto &ch : vec)
        cout << ch << " ";
    cout << endl;
}

// Allowed Directions
const vector<pair<int, int>> directions = {
    { 0, 0 },  // Current node
    { -1, 0 }, // top
    { -1, 1 }, // top-right
    { 0, 1 },  // right
    { 1, 1 },  // bottom-right
    { 1, 0 },  // bottom
    { 1, -1 }, // bottom-left
    { 0, -1 }, // left
    { -1, -1 } // top-left
};

const string SEARCH_WORD = "XMAS";

// Forward Declarations
// Read & store the input data as a matrix of char's
vector<vector<char>> matrix;
int rows { 0 }, cols { 0 };

int dfs(int find_idx, int row, int col, int dir)
{
    // Base Case:
    if (SEARCH_WORD[find_idx] != matrix[row][col]) {
        return 0;
    }

    // Out of bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return 0;
    }

    // Explore for next char in the given direction
    // 1. If we explored 1st direction, can explore in
    if (dir == 0) {
    }

    return 9999;
}

int main()
{
    cout << "--------------\nDAY-04 Part-01\n--------------" << endl;

    // Read the input file
    std::ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    string line;

    while (getline(file, line)) {
        vector<char> row;
        for (char ch : line) {
            row.push_back(ch);
        }
        printVector(row);
        matrix.push_back(row);
    }

    // Set the values of forward declarations
    rows = matrix.size();
    cols = matrix[0].size();

    int result { 0 };

    // Go over the grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            result += dfs(0, row, col, 0);
        }
    }

    cout << "--------------\n";
    cout << "RESULT: " << result << endl;
    cout << "--------------" << endl;

    file.close();

    return 0;
}
