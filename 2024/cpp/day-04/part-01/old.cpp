#include <iostream>
#include <string>
#include <vector>

#pragma region using-statments
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;
#pragma endregion

// Allowed Directions
const vector<pair<int, int>> directions = {
    // { 0, 0 },  // Current node
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

int exploreInGivenDirection(int find_idx, int parentRow, int parentCol,
                            pair<int, int> dir)
{
    int row { parentRow + dir.first }, col { parentCol + dir.second };

    // Base Case: Out of bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return 0;
    }

    // Base Case: Matched and is the last letter of search word
    if (find_idx == 3 && SEARCH_WORD[find_idx] == matrix[row][col]) {
        return 1;
    }

    // Current letter matches: Explore next letter in the same direction
    if (SEARCH_WORD[find_idx] == matrix[row][col]) {
        return exploreInGivenDirection(find_idx + 1, row, col, dir);
    }

    // Current letter doesn't match
    return 0;
}

int main()
{
    cout << "--------------\nDAY-04 Part-01\n--------------" << endl;

    string line;

    for (int i = 1; i <= 140; i++) {
        std::cin >> line;
        vector<char> row;
        for (char ch : line) {
            row.push_back(ch);
        }
        matrix.push_back(row);
    }

    // Set the values of forward declarations
    rows = matrix.size();
    cols = matrix[0].size();

    int result { 0 };

    // Go over the grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {

            // If letter is 'X' => explore all 8 directions
            if (matrix[row][col] == 'X') {
                for (auto &dir : directions) {
                    result += exploreInGivenDirection(1, row, col, dir);
                }
            }
        }
    }

    cout << "--------------\n";
    cout << "RESULT: " << result << endl;
    cout << "--------------" << endl;

    // file.close();

    return 0;
}
