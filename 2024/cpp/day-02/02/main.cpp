// https://adventofcode.com/2024/day/2

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define FILE_PATH "./2024/cpp/day-02/01/test.txt"

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

// HELPER: Validate the vector of numbers for a given sequence
bool validateVector(const vector<int> &nums, bool isIncreasing)
{
    int diff = abs(nums[0] - nums[1]);
    if (diff <= 0 || diff > 3) {
        // cout << "E1\n";
        return false;
    }

    int prevNumber { nums[0] };
    for (int i = 1; i < nums.size(); ++i) {
        int currNumber = nums[i];

        int diff =
            isIncreasing ? currNumber - prevNumber : prevNumber - currNumber;
        if (diff <= 0 || diff > 3) {
            // cout << "E2\n";
            return false;
        }
        prevNumber = currNumber;
    }
    return true;
}

bool validateVectorWithTolerance(const vector<int> &nums, bool isIncreasing)
{
    // EDGE case:
    if (abs(nums[0] - nums[1]) == 0) {
        cout << "E1\n";
        return false;
    }

    // int diff = abs(nums[0] - nums[1]);
    // if (diff <= 0 || diff > 3) {
    //     // cout << "E1\n";
    //     return false;
    // }

    int prevNumber { nums[0] };
    for (int i = 1; i < nums.size(); ++i) {
        int currNumber = nums[i];

        int diff =
            isIncreasing ? currNumber - prevNumber : prevNumber - currNumber;
        if (diff <= 0 || diff > 3) {
            // cout << "E2\n";
            return false;

            // Create a new vector with out this breaking item

            // Variant-1: Ignore i'th
            vector<int> variant1_left(nums.begin(), nums.begin() + i);
            vector<int> variant1_right(nums.begin() + i + 1, nums.end());
            vector<int> variant1_final = variant1_left;
            variant1_final.insert(variant1_final.end(), variant1_right.begin(),
                                  variant1_right.end());
            if (validateVector(variant1_final, isIncreasing))
                return true;

            // Variant-2: Ignore i-1'th
            vector<int> variant2_left(nums.begin(), nums.begin() + i - 1);
            vector<int> variant2_right(nums.begin() + i, nums.end());
            vector<int> variant2_final = variant2_left;
            variant2_final.insert(variant2_final.end(), variant2_right.begin(),
                                  variant2_right.end());
            if (validateVector(variant2_final, isIncreasing))
                return true;

            cout << "E2\n";
            return false;
        }
        prevNumber = currNumber;
    }
    return true;
}

bool isValidWithToleration(const string &line)
{
    vector<int> nums;

    istringstream iss(line);

    int num;
    while (iss >> num) {
        nums.push_back(num);
    }

    // 1. Determine direction
    bool isIncreasing = nums[0] < nums[1];

    // return validateVector(nums, isIncreasing);
    return validateVectorWithTolerance(nums, isIncreasing);
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
        if (isValidWithToleration(line)) {
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
