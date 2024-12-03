#include <fstream>
#include <iostream>
#include <string>

#pragma region using-statments
// using namespace std;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
#pragma endregion

#pragma region Program-Constants
const string FILE_PATH = "./2024/cpp/day-03/part-01/test.txt";
// const string FILE_PATH = "./2024/cpp/day-03/part-01/input.txt";
#pragma endregion

int main()
{
    // cout << "DAY-03 PART-01" << endl;

    // Read the input file
    std::ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    string line;

    while (getline(file, line)) {
        cout << line << endl;
    }

    return 0;
}
