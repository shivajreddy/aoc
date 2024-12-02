// https://adventofcode.com/2024/day/2

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define FILE_PATH "./2024/cpp/day-02/01/input.txt"

bool isValidLine(const string &line, bool removeCurrentNumber = false)
{
    istringstream iss(line);
    int prevNumber, currNumber;

    // Read the first two numbers to establish direction and initial diff
    if (!(iss >> prevNumber) || !(iss >> currNumber)) {
        return false; // Invalid line if fewer than two numbers
    }

    // Determine increasing or decreasing direction
    bool isIncreasing = prevNumber < currNumber;

    // Check absolute difference to be within a difference of 3
    int diff = abs(prevNumber - currNumber);
    if (diff <= 0 || diff > 3) {
        return false;
    }

    prevNumber = currNumber; // Update previous before next iteration

    // Process the rest of the numbers
    while (iss >> currNumber) {
        // Check absolute difference to be within a difference of 3
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

bool isValidWithToleration(const string &line)
{
    // Try removing each number and check if the resulting line is valid
    istringstream iss(line);
    string currentLine;
    string tempLine;
    string skipNumber;

    while (getline(iss, skipNumber, ' ')) {
        // Reconstruct the line without the current number
        tempLine.clear();

        istringstream originalIss(line);
        string number;

        while (getline(originalIss, number, ' ')) {
            if (number != skipNumber) {
                if (!tempLine.empty()) {
                    tempLine += " ";
                }
                tempLine += number;
            }
        }

        // Check if the line without the current number is valid
        if (isValidLine(tempLine)) {
            return true;
        }
    }

    return false;
}

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
        if (isValidLine(line) || isValidWithToleration(line)) {
            safeReports += 1;
        }
    }

    cout << "RESULT: " << safeReports << endl;
    return 0;
}

/*
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

bool isValidWithToleration(const string &line)
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
        // Is valid by remove first or second
        return isValidLine(line_with_out_first_number) ||
               isValidLine(line_with_out_second_number);
    }

    prevNumber = currNumber; // Update previous before next iteration

    // Process the rest of the numbers
    while (iss >> currNumber) {

        // Check absolute difference to be with in a difference of 3
        diff = abs(prevNumber - currNumber);
        if (diff <= 0 || diff > 3) {
            return isValidLine(line_with_out_current_number);
        }

        // Validate direction
        if ((isIncreasing && currNumber <= prevNumber) ||
            (!isIncreasing && currNumber >= prevNumber)) {
            // Inconsistent direction
            return isValidLine(line_with_out_current_number);
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

        if (isValidLine(line) || isValidWithToleration(line))
            safeReports += 1;
    }

    cout << "RESULT: " << safeReports << endl;

    return 0;
}
*/
