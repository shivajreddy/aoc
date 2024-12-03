// https://adventofcode.com/2024/day/2

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define FILE_PATH "./2024/cpp/day-02/02/test.txt"
// #define FILE_PATH "./2024/cpp/day-02/02/input.txt"

/*
    8 2 3 4 6
    |

    2 8 9 10 11
    |

    3 1 5 7 8 9
        |

    1 6 3 4 5 7
        |
*/

bool validStrictIncreasing(const vector<int> &nums)
{
    if (nums.empty() || nums.size() == 1)
        return true;

    for (int i = 1; i < nums.size(); ++i) {
        int diff = nums[i] - nums[i - 1];
        if (diff <= 0 || diff > 3)
            return false;
    }
    return true;
}

bool validStrictDecreasing(const vector<int> &nums)
{
    if (nums.empty() || nums.size() == 1)
        return true;

    for (int i = 1; i < nums.size(); ++i) {
        int diff = nums[i - 1] - nums[i];
        if (diff <= 0 || diff > 3)
            return false;
    }
    return true;
}

bool validIncreasing(const vector<int> &nums)
{
    if (nums.empty())
        return false;

    int allowedTolerance = 1;
    int maxDiff = 3;

    int prevNumber = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        int currNumber = nums[i];
        int diff = currNumber - prevNumber;

        // Check if the sequence is broken
        if (diff <= 0 || diff > maxDiff) {
            // No more tolerances, return false
            if (allowedTolerance == 0) {
                return false;
            }
            allowedTolerance--;
        } else {
            prevNumber = currNumber;
        }
    }
    return true;
}

bool validDecreasing(const vector<int> &nums)
{
    if (nums.empty())
        return false;

    int allowedTolerance = 1;
    int maxDiff = 3;

    int prevNumber = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        int currNumber = nums[i];
        int diff = prevNumber - currNumber;

        // Check if the sequence is broken
        if (diff <= 0 || diff > maxDiff) {
            // No more tolerances, return false
            if (allowedTolerance == 0) {
                return false;
            }
            allowedTolerance--;
        } else {
            prevNumber = currNumber;
        }
    }
    return true;
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

        // Create a vector of numbers
        vector<int> nums;
        istringstream iss(line);
        int num;
        while (iss >> num) {
            nums.push_back(num);
        }

        if (validIncreasing(nums) || validDecreasing(nums)) {
            safeReports += 1;
            cout << "✅ " << endl;
        } else {
            cout << "❌ " << endl;
        }
    }
    cout << "\nRESULT: " << safeReports << endl;
    return 0;
}
