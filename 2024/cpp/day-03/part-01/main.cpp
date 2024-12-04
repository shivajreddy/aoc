#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#pragma region using-statments
// using namespace std;
using std::cerr;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;
#pragma endregion

#pragma region Program-Constants
const string FILE_PATH = "./2024/cpp/day-03/part-01/test.txt";
// const string FILE_PATH = "./2024/cpp/day-03/part-01/input.txt";
#pragma endregion

// HELPER : Find the start,end indexes of matching regular expression
struct MatchInfo
{
    string match;
    size_t start;
    size_t end;
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

            // Store match information
            MatchInfo newMatch { match.str(), (size_t)match.position(),
                                 (size_t)(match.position() + match.length()) };
            matches.push_back(newMatch);
        }
    }
    catch (std::regex_error &e) {
        std::cerr << "Regex error: " << e.what() << std::endl;
    }

    return matches;
}

int findTotal(vector<MatchInfo> matches)
{
    int result { 0 };
    for (auto &match : matches) {
        int x = match.match[]
    }
    return result;
}

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

    // Regular Expression
    string regularExpression =
        "mul\\((\\d\\d\\d,|\\d\\d,|\\d,)(\\d\\d\\d|\\d\\d|\\d)\\)";

    string line;

    while (getline(file, line)) {
        cout << line << endl;

        auto res = findRegexMatches(line, regularExpression);

        cout << res.size() << endl;
    }

    file.close();

    return 0;
}
