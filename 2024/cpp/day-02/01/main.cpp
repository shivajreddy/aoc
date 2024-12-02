// https://adventofcode.com/2024/day/2

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string FILE_PATH { "./2024/cpp/day-02/01/input.txt" };

// int day_01_part_01_main() {
int main()
{
    // Read the input file
    ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    vector<int> leftNumbers, rightNumbers;

    string line;
    while (getline(file, line)) {
        // Create a string stream object
        istringstream iss(line);

        // Variables to hold the numbers
        int leftNumber, rightNumber;

        // Extract the numbers from the string
        iss >> leftNumber >> rightNumber;

        leftNumbers.push_back(leftNumber);
        rightNumbers.push_back(rightNumber);
    }

    // Sort leftNumbers & rightNumber : 2.n.log(n)
    sort(leftNumbers.begin(), leftNumbers.end());
    sort(rightNumbers.begin(), rightNumbers.end());

    int result = 0;

    for (int i = 0; i < leftNumbers.size(); ++i) {
        result += abs(leftNumbers[i] - rightNumbers[i]);
    }

    cout << "RESULT: " << result << endl;

    return 0;
}
