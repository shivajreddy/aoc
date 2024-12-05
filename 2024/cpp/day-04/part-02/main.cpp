/*
Goal of the problem
    - We are search with 'A' as root node
    - Edges from root node: where each edge has two nodes
        [Top-Left, Bottom-Right] & [Top-Right, Bottom-Left]
        - Both nodes of both the edges should be valid
            - Validity for nodes for each edge:
                - nodes are in bound
                - two values for the two nodes are 'M','S' or 'S','M'

Time : O(M*N), for M rows and N columns
Space: O(M*N)
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

// -----------------------------------------------------------------
// Forward Declarations
// -----------------------------------------------------------------
vector<vector<char>> matrix;
int rows { 0 }, cols { 0 };

// -----------------------------------------------------------------
// Helper Fns
// -----------------------------------------------------------------
void printVector(vector<char> vec)
{
    for (auto &ch : vec)
        cout << ch << " ";
    cout << endl;
}

// -----------------------------------------------------------------
// Program Constants
// -----------------------------------------------------------------
// const string FILE_PATH = "./2024/cpp/day-04/part-02/test.txt";
const string FILE_PATH = "./2024/cpp/day-04/part-02/input.txt";

// For a given node, which is 'A', check if it forms X shaped 'MAS'
bool checkForX_MAS(int row, int col)
{
    // LeftSlash => \ .
    bool leftSlash { false };

    // LeftSlash nodes -> top-left & bottom-right
    int topLeftRow = row - 1;
    int topLeftCol = col - 1;
    int bottomRightRow = row + 1;
    int bottomRightCol = col + 1;

    if (topLeftRow < 0 || topLeftCol < 0 || bottomRightRow >= rows ||
        bottomRightCol >= cols)
        return false;

    //  \ => M.A.S
    if (matrix[topLeftRow][topLeftCol] == 'M' &&
        matrix[bottomRightRow][bottomRightCol] == 'S')
        leftSlash = true;

    //  \ => S.A.M
    if (matrix[topLeftRow][topLeftCol] == 'S' &&
        matrix[bottomRightRow][bottomRightCol] == 'M')
        leftSlash = true;

    // RightSlash => / .
    bool rightSlash { false };

    // RightSlash nodes -> top-right & bottom-left
    int topRightRow = row - 1;
    int topRightCol = col + 1;
    int bottomLeftRow = row + 1;
    int bottomLeftCol = col - 1;

    if (topRightRow < 0 || topRightCol >= cols || bottomLeftRow >= rows ||
        bottomLeftCol < 0)
        return false;

    //  / => S.A.M
    if (matrix[topRightRow][topRightCol] == 'M' &&
        matrix[bottomLeftRow][bottomLeftCol] == 'S')
        rightSlash = true;

    //  / => S.A.M
    if (matrix[topRightRow][topRightCol] == 'S' &&
        matrix[bottomLeftRow][bottomLeftCol] == 'M')
        rightSlash = true;

    return leftSlash && rightSlash;
}

// -----------------------------------------------------------------
// Entry Point
// -----------------------------------------------------------------
int main()
{
    cout << "--------------\nDAY-04 Part-02\n--------------" << endl;

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
        matrix.push_back(row);
    }

    // Set the values of forward declarations
    rows = matrix.size();
    cols = matrix[0].size();

    int result { 0 };

    // Go over the grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {

            // If letter is 'A' => explore edges
            if (matrix[row][col] == 'A') {
                if (checkForX_MAS(row, col))
                    result += 1;
            }
        }
    }

    cout << "RESULT: " << result << endl;

    file.close();

    return 0;
}
