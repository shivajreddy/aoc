#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------------------------------
// Convert the string line into vector of numbers
// -----------------------------------------------------------------
vector<int> getNumbers(const string &line)
{
    vector<int> result;
    int num = 0;
    for (char curr : line) {
        if (curr == ' ' || curr == ':') {
            if (num != 0) {
                result.push_back(num);
                num = 0;
            }
        } else if (isdigit(curr)) {
            num = num * 10 + (curr - '0');
        }
    }
    if (num != 0) {
        result.push_back(num);
    }
    return result;
}

bool isValid(vector<int> nums, int currResult, int idx)
{
    cout << "idx:" << idx << " currResult: " << currResult << endl;

    int total = nums[0];

    // Base Case: Past the list
    if (idx >= nums.size()) {
        cout << "\n";
        return total == currResult;
    }

    if (idx == 1) {
        currResult = nums[1];
        return isValid(nums, currResult, idx + 1);
    }

    idx += 1;
    for (; idx < nums.size(); idx++) {
        int num = nums[idx];
        return isValid(nums, currResult + num, idx) ||
               isValid(nums, currResult * num, idx);
    }
    return false;
}

// -----------------------------------------------------------------
// Entry Point
// -----------------------------------------------------------------
int main()
{
    cout << "--------------\nDAY-07 Part-01\n--------------" << endl;

    // Read input
    vector<string> a;
    string line;
    while (getline(cin, line)) {
        a.push_back(line);
    }

    vector<vector<int>> matrix;
    for (auto &line : a) {
        vector<int> row = getNumbers(line);
        matrix.push_back(row);
    }

    int answer = 0;
    for (auto &row : matrix) {
        if (isValid(row, -1, 0)) {
            answer += row[0];
        }
    }

    cout << "ANSWER: " << answer << endl;

    return 0;
}
