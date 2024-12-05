/*
Goal:

Time :
Space:
*/

#include <fstream>
#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

// -----------------------------------------------------------------
// Forward Declarations
// -----------------------------------------------------------------

// -----------------------------------------------------------------
// Helper Fns
// -----------------------------------------------------------------

// -----------------------------------------------------------------
// Program Constants
// -----------------------------------------------------------------
// const string FILE_PATH = "./2024/cpp/day-05/part-01/test.txt";
const string FILE_PATH = "./2024/cpp/day-05/part-01/input.txt";

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

    string line;

    while (getline(file, line)) {
        cout << line << endl;
    }

    int result { 0 };

    cout << "RESULT: " << result << endl;

    file.close();

    return 0;
}
