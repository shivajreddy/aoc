/*
Goal:

Time :
Space:
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
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
const string FILE_PATH = "./2024/cpp/day-05/part-01/test.txt";
// const string FILE_PATH = "./2024/cpp/day-05/part-01/input.txt";

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
// TODO: Fix the incorrectly-ordered line
// -----------------------------------------------------------------
int fixIncorectOrderAndGetMiddle(const vector<int> &nums)
{
    vector<std::shared_ptr<Node>> nodes;

    // Map the numbers to their corresponding graph nodes
    for (int num : nums) {
        if (graph.find(num) != graph.end()) {
            nodes.push_back(graph[num]);
        }
    }

    // Reorder the nodes based on graph relationships
    vector<int> fixedOrder;
    std::unordered_set<std::shared_ptr<Node>> visited;
    std::queue<std::shared_ptr<Node>> toVisit;

    // Start with the first node in the input order
    if (!nodes.empty()) {
        toVisit.push(nodes.front());
    }

    while (!toVisit.empty()) {
        auto current = toVisit.front();
        toVisit.pop();

        if (visited.find(current) != visited.end()) {
            continue;
        }

        visited.insert(current);
        fixedOrder.push_back(current->key);

        // Add children to the queue in order
        for (auto &child : current->children) {
            if (visited.find(child) == visited.end()) {
                toVisit.push(child);
            }
        }
    }

    cout << "FIXED ORDER: ";
    for (int num : fixedOrder) {
        cout << num << " ";
    }
    cout << endl;

    // Return the middle element of the reordered list
    size_t middleIndex = fixedOrder.size() / 2;
    return fixedOrder[middleIndex];
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

            // Consider only wrong order lines
            if (!isValidateOrder(nums)) {
                cout << "GIVEN ORDER: " << line << endl;
                // Fix them and get the middle number
                int middleNumber = fixIncorectOrderAndGetMiddle(nums);
                result += middleNumber;
            }
        }
    }

    cout << "RESULT: " << result << endl;
    // 5025 <- too low

    file.close();

    return 0;
}
