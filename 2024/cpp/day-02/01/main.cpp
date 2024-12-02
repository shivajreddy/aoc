// https://adventofcode.com/2024/day/2

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string FILE_PATH { "./2024/cpp/day-02/01/input.txt" };

bool isValidLine(const std::string &line)
{
    std::istringstream iss(line);
    int prevNumber, currNumber;

    // Read the first two numbers to establish direction and initial diff
    if (!(iss >> prevNumber) || !(iss >> currNumber)) {
        return false; // Invalid line if fewer than two numbers
    }

    // Determine increasing or decreasing direction
    bool isIncreasing = prevNumber < currNumber;

    // Check absolute difference to be with in a difference of 3
    int diff = abs(prevNumber - currNumber);
    if (diff <= 0 || diff > 3) {
        return false;
    }

    prevNumber = currNumber; // Update previous before next iteration

    // Process the rest of the numbers
    while (iss >> currNumber) {

        // Check absolute difference to be with in a difference of 3
        diff = abs(prevNumber - currNumber);
        if (diff <= 0 || diff > 3) {
            return false;
        }

        // Validate direction
        if ((isIncreasing && currNumber <= prevNumber) ||
            (!isIncreasing && currNumber >= prevNumber)) {
            return false; // Inconsistent direction
        }

        prevNumber = currNumber; // Update previous before next iteration
    }

    return true;
}

// int day_02_part_01_main() {
int main()
{
    // Read the input file
    ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    int safeReports = 0;

    string line;
    while (getline(file, line)) {

        if (isValidLine(line))
            safeReports += 1;
    }

    cout << "RESULT: " << safeReports << endl;

    return 0;
}
