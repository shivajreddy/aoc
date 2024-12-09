#include <iostream>
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------------------------------
// Program Constants
// -----------------------------------------------------------------
const char GUARD = '^';
const char OBSTACLE = '#';
const char EMPTY = '.';

// -----------------------------------------------------------------
// Entry Point
// -----------------------------------------------------------------
int main()
{
    // Create Matrix & Find the starting position
    vector<vector<char>> matrix;
    pair<int, int> startPosition { -1, -1 };
    string line;
    int rowIdx = 0;

    while (cin >> line) {
        vector<char> row;
        for (int c = 0; c < (int)line.length(); c++) {
            char ch = line[c];
            if (ch == GUARD) {
                startPosition = { rowIdx, c };
            }
            row.push_back(ch);
        }
        matrix.push_back(row);
        rowIdx += 1;
    }

    int steps = 1; // GUARD's initial position is also counted as 1 step

    int rows = matrix.size();
    int cols = matrix[0].size(); // Fixed column count

    vector<pair<int, int>> directions = {
        { -1, 0 }, // TOP
        { 0, 1 },  // RIGHT
        { 1, 0 },  // BOTTOM
        { 0, -1 }, // LEFT
    };

    int r = startPosition.first;
    int c = startPosition.second;

    int dir = 0; // Start moving in the TOP direction
    while (true) {
        // Calculate the next position
        int nextR = r + directions[dir].first;
        int nextC = c + directions[dir].second;

        // Check bounds before accessing the matrix
        if (nextR < 0 || nextR >= rows || nextC < 0 || nextC >= cols) {
            cout << "ANSWER: " << steps << endl;
            return 0;
        }

        char curr = matrix[nextR][nextC];

        if (curr == EMPTY) {
            // Move and mark as visited
            matrix[nextR][nextC] = GUARD;
            r = nextR;
            c = nextC;
            steps += 1;
        } else if (curr == GUARD) {
            // Move forward without increasing steps
            r = nextR;
            c = nextC;
        } else if (curr == OBSTACLE) {
            // Change direction clockwise
            dir = (dir + 1) % 4;
        }
    }

    // This point should never be reached
    cout << "ANSWER: " << steps << endl;

    return 0;
}
