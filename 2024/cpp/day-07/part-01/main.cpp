#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------------------------------
// Program Constants
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

    for (auto &item : a) {
        cout << "item:" << item << endl;

        vector<int> nums = getNumbers(line);
        for (auto &num : nums)
            cout << "num:" << num << ",";
        // cout << endl;
    }

    return 0;
}
