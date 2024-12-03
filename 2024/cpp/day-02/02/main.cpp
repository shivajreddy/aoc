// https://adventofcode.com/2024/day/2

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

#pragma region Problem - Constants
const string FILE_PATH = "./2024/cpp/day-02/02/input.txt";
const int MIN_ABSOLUTE_DIFFERENCE = 0;
const int MAX_ABSOLUTE_DIFFERENCE = 3;
#pragma endregion

// HELPER : Create a new vector copy by removing target index
vector<int> createVectorCopyBySkippingIndex(const vector<int> &nums, int idx)
{
    vector<int> slice1(nums.begin(), nums.begin() + idx);
    vector<int> slice2(nums.begin() + idx + 1, nums.end());

    vector<int> combined = slice1;
    combined.insert(combined.end(), slice2.begin(), slice2.end());

    return combined;
}

bool isStrictSequence(const vector<int> &nums, bool isIncreasingSequence)
{
    if (nums.empty() || nums.size() == 1)
        return true;

    for (int i = 1; i < nums.size(); ++i) {

        int diff = isIncreasingSequence ? nums[i] - nums[i - 1]
                                        : nums[i - 1] - nums[i];

        if (diff <= MIN_ABSOLUTE_DIFFERENCE || diff > MAX_ABSOLUTE_DIFFERENCE)
            return false;
    }
    return true;
}

bool isValidSequence(const vector<int> &nums, bool isIncreasingSequence)
{
    if (nums.empty())
        return false;

    for (int i = 1; i < nums.size(); ++i) {

        int diff = isIncreasingSequence ? nums[i] - nums[i - 1]
                                        : nums[i - 1] - nums[i];

        // Check if sequence is broken
        if (diff <= 0 || diff > 3) {

            // Ignore i'th number
            auto variant1 = createVectorCopyBySkippingIndex(nums, i);

            // Ignore (i-1)'th number
            auto variant2 = createVectorCopyBySkippingIndex(nums, i - 1);

            return isStrictSequence(variant1, isIncreasingSequence) ||
                   isStrictSequence(variant2, isIncreasingSequence);
        }
    }
    return true;
}

int main()
{
    // Read the input file
    std::ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    int safeReports = 0;
    string line;

    while (getline(file, line)) {
        // 1. Create a vector of numbers
        vector<int> nums;
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            nums.push_back(num);
        }

        // 2. Check if this line is a valid 'increasing or deceasing' sequence
        if (isValidSequence(nums, true) || isValidSequence(nums, false)) {
            safeReports += 1;
        }
    }

    std::cout << "RESULT: " << safeReports << std::endl;
    return 0;
}
