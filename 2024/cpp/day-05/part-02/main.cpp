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
using std::string;
using std::vector;

// -----------------------------------------------------------------
// Program Constants
// -----------------------------------------------------------------
// const string FILE_PATH = "./2024/cpp/day-05/part-01/test.txt";
const string FILE_PATH = "./2024/cpp/day-05/part-01/input.txt";

// -----------------------------------------------------------------
// Forward Declarations
// -----------------------------------------------------------------
struct Node
{
    int key; // The number itself
    std::unordered_set<std::shared_ptr<Node>>
        children; // Set of pointers to children

    explicit Node(int key) : key(key) {}
};

// -----------------------------------------------------------------
// All nodes in the graph
// -----------------------------------------------------------------
std::unordered_map<int, std::shared_ptr<Node>> graph;

// A Page rule is a directed edge in the graph, leftNumber -> rightNumber
void insertIntoGraph(const string &line)
{
    // Get delimiter position
    size_t idx = line.find('|');

    if (idx == string::npos)
        return;

    int leftKey = std::stoi(line.substr(0, idx));
    int rightKey = std::stoi(line.substr(idx + 1));

    std::shared_ptr<Node> leftNode, rightNode;

    // Create or retrieve the left node
    if (graph.find(leftKey) == graph.end()) {
        leftNode = std::make_shared<Node>(leftKey);
        graph[leftKey] = leftNode;
    } else {
        leftNode = graph[leftKey];
    }

    if (graph.find(rightKey) == graph.end()) {
        rightNode = std::make_shared<Node>(rightKey);
        graph[rightKey] = rightNode;
    } else {
        rightNode = graph[rightKey];
    }

    // Set right node to be one of leftNode's children
    leftNode->children.insert(rightNode);
}

// -----------------------------------------------------------------
// Covert the string of page numbers to vector<int>
// -----------------------------------------------------------------
vector<int> convertToVector(const string &line)
{
    vector<int> nums;
    std::stringstream ss(line);
    string item;
    while (getline(ss, item, ',')) {
        nums.push_back(std::stoi(item));
    }
    return nums;
}

// -----------------------------------------------------------------
// Check if the given order of numbers are a valid path in graph
// -----------------------------------------------------------------
bool isValidateOrder(const vector<int> &nums)
{

    std::shared_ptr<Node> prev { nullptr };

    for (int num : nums) {

        // Number doesn't exist in graph
        if (graph.find(num) == graph.end()) {
            return false;
        }

        std::shared_ptr<Node> curr = graph[num];

        // First node
        if (prev == nullptr) {
            prev = curr;
        } else {
            // Check if current node is one of previous node's children
            if (prev->children.find(curr) == prev->children.end())
                return false;

            // Update previous
            prev = curr;
        }
    }

    return true;
}

// -----------------------------------------------------------------
// Entry Point
// -----------------------------------------------------------------
int main()
{
    cout << "--------------\nDAY-05 Part-02\n--------------" << endl;

    // Read the input file
    std::ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    int result { 0 };

    // Variables for storing input data
    bool isSection1 { true };

    // Read input data & store them in memory
    string line;
    while (getline(file, line)) {
        if (line == "") { // Empty line marks the break of section-1
            isSection1 = false;
        } else if (isSection1) {
            insertIntoGraph(line);
            // cout << "Total Nodes" << graph.size() << endl;
        } else {
            vector<int> nums = convertToVector(line);

            if (isValidateOrder(nums)) {
                int middleNumber = nums[(int)(nums.size() / 2)];
                result += middleNumber;
            }
        }
    }

    cout << "RESULT: " << result << endl;

    file.close();

    return 0;
}
