#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#pragma region using-statments
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;
#pragma endregion

#pragma region Program-Constants
const string FILE_PATH = "./2024/cpp/day-03/part-01/input.txt";
#pragma endregion

struct MatchInfo
{
    string match;
    size_t start;
    size_t end;
    int x;
    int y;
};

vector<MatchInfo> findRegexMatches(const string &text, const string &pattern)
{
    vector<MatchInfo> matches;

    try {
        // Create regex object
        std::regex re(pattern);

        // Iterate to find all matches
        auto wordBegin = std::sregex_iterator(text.begin(), text.end(), re);
        auto wordEnd = std::sregex_iterator();

        // Iterate over matches
        for (std::sregex_iterator i = wordBegin; i != wordEnd; ++i) {
            std::smatch match = *i;

            // Extract the match and positions
            string fullMatch = match.str();
            size_t start = match.position();
            size_t end = start + match.length();

            // Extract x and y from the capturing groups
            int x = std::stoi(match[1].str()); // First capture group
            int y = std::stoi(match[2].str()); // Second capture group

            // Store match information
            MatchInfo newMatch { fullMatch, start, end, x, y };
            matches.push_back(newMatch);
        }
    }
    catch (std::regex_error &e) {
        std::cerr << "Regex error: " << e.what() << std::endl;
    }

    return matches;
}

int main()
{
    // Read the input file
    std::ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    // Regular Expression, that match mul(x,y)
    string regularExpression = "mul\\((\\d{1,3}),\\s*(\\d{1,3})\\)";

    string line;

    int result { 0 };

    while (getline(file, line)) {

        // Create Pattern Matches
        auto allMatches = findRegexMatches(line, regularExpression);

        for (auto &match : allMatches) {
            result += (match.x * match.y);
        }
    }
    cout << "RESULT: " << result << endl;

    file.close();

    return 0;
}
