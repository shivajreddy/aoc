// https://adventofcode.com/2024/day/1

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

const string FILE_PATH { "./2024/cpp/day-01/02/input.txt" };

// int day_01_part_02_main() {
int main()
{
    // Read the input file
    ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    // Hashmap of left numbers and right numbers
    unordered_map<int, int> leftMap, rightMap;

    string line;
    while (getline(file, line)) {
        // Create a string stream object
        istringstream iss(line);

        // Variables to hold the numbers
        int leftNumber, rightNumber;

        // Extract the numbers from the string
        iss >> leftNumber >> rightNumber;

        leftMap[leftNumber] += 1;
        rightMap[rightNumber] += 1;
    }

    int result = 0;

    for (const auto &[leftNum, leftCount] : leftMap) {

        // If left number exists in right hashmap
        if (rightMap.find(leftNum) != rightMap.end()) {
            int rightCount = rightMap[leftNum];
            // multiply with leftCount for all similar left numbers
            result += leftNum * rightCount * leftCount;
        }
    }

    cout << "RESULT: " << result << endl;

    return 0;
}
