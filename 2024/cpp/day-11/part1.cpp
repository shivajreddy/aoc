#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
/*

blink -> stone num changes || stone splits in two

Rules:
0 -> 1
len(num)%2 -> split to two, left half digits | right half digits(with out
leading zeroes)
* 2024

0     1      10      99      999
1   2024    1  0    9  9   99*2024
*/

// HELPER
void printVector(const vector<int> &v)
{
    for (auto &num : v) {
        cout << num << " ";
    }
    cout << endl;
}

void createNewStones(int stone, vector<int> &result)
{
    // Rule 1
    if (stone == 0) {
        result.push_back(1);
        return;
    }
    // Rule 2
    string num = to_string(stone);
    if (num.size() % 2 == 0) {
        string left = num.substr(0, (int)num.size() / 2);
        string right = num.substr((int)num.size() / 2);
        result.push_back(stoi(left));
        result.push_back(stoi(right));
        return;
    }

    // TODO: Handle overflow
    result.push_back((stone * 2024));
    return;
}

int main()
{
    // cout << "DAY 11 PART 1" << endl;

    string line;
    getline(cin, line); // Only a single line input

    vector<int> stones {};

    int stone;
    istringstream iss(line); // Create a string stream
    while (iss >> stone) {
        stones.push_back(stone);
    }

    int blinkTimes = 0;
    const int TOTAL_BLINK_TIMES = 25;
    while (blinkTimes < TOTAL_BLINK_TIMES) {
        vector<int> newStones = {};

        for (auto &stone : stones) {
            createNewStones(stone, newStones);
        }
        stones = newStones;
        blinkTimes++;

        cout << "\nAfter " << blinkTimes << " blinks:" << endl;
        printVector(stones);
    }

    cout << "\nANSWER: " << stones.size() << endl;

    return 0;
}
