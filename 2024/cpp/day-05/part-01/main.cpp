/*
Goal:

Time :
Space:
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

// -----------------------------------------------------------------
// Forward Declarations
// -----------------------------------------------------------------
struct Node
{
    int key;                             // The number itself
    std::unordered_set<Node *> children; // Set of pointers to children

    explicit Node(int k) : key(k) {}
};

// All nodes for the program
std::unordered_map<std::string, std::shared_ptr<Node>> allNodes;

// -----------------------------------------------------------------
// Program Constants
// -----------------------------------------------------------------
const string FILE_PATH = "./2024/cpp/day-05/part-01/test.txt";
// const string FILE_PATH = "./2024/cpp/day-05/part-01/input.txt";

// -----------------------------------------------------------------
// Helper Fns
// -----------------------------------------------------------------
pair<int, int> getPageOrderingRules(const string &line)
{
    // Get delimiter position
    size_t idx = line.find('|');
    if (idx == string::npos)
        return { 0, 0 };

    return { std::stoi(line.substr(0, idx)), std::stoi(line.substr(idx + 1)) };
}

vector<int> getNumbers(const string &line)
{
    vector<int> result;
    std::stringstream ss(line);

    string item;
    while (getline(ss, item, ',')) {
        result.push_back(std::stoi(item));
    }

    return result;
}

// -----------------------------------------------------------------
// Check if given path is valid
// -----------------------------------------------------------------
bool isValidPath()

    // -----------------------------------------------------------------
    // Entry Point
    // -----------------------------------------------------------------
    int main()
{
    cout << "--------------\nDAY-05 Part-01\n--------------" << endl;

    // Read the input file
    std::ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    // Variables for storing input data
    bool isSection1 { true };
    vector<pair<int, int>> orderingRules; // section-1
    vector<vector<int>> pageNumbers;      // section-2

    // Read input data & store them in memory
    string line;
    while (getline(file, line)) {
        if (line == "\n") {
            isSection1 = false;
        } else if (isSection1) {
            orderingRules.push_back(getPageOrderingRules(line));
        } else {
            pageNumbers.push_back(getNumbers(line));
        }
    }

    int result { 0 };

    cout << "RESULT: " << result << endl;

    file.close();

    return 0;
}
