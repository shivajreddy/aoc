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
// const string FILE_PATH = "./2024/cpp/day-03/part-02/test.txt";
const string FILE_PATH = "./2024/cpp/day-03/part-02/input.txt";
#pragma endregion

struct Match1
{
    string match;
    size_t start;
    size_t end;
    int x;
    int y;
};

struct Match2
{
    size_t start;
    size_t end;
    bool isDo; // true for 'do()' false for 'don't()'
};

vector<Match2> findRegex2Matches(const string &text, const string &pattern)
{
    vector<Match2> result;
    try {
        // Create Regex object
        std::regex re(pattern);

        // Find all regex matches for given text
        auto wordBegin = std::sregex_iterator(text.begin(), text.end(), re);
        auto wordEnd = std::sregex_iterator();

        // Iterate over the matches
        for (std::sregex_iterator i = wordBegin; i != wordEnd; ++i) {
            std::smatch match = *i;

            size_t start = match.position();
            size_t end = start + match.length();
            bool isDo = match.str() == "do()";

            Match2 reg2Match { start, end, isDo };
            result.push_back(reg2Match);
        }
    }
    catch (std::regex_error &error) {
        cerr << "Reg2Match-ERROR: " << error.what() << endl;
    }
    return result;
}

vector<Match1> findRegex1Matches(const string &text, const string &pattern)
{
    vector<Match1> matches;

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
            Match1 newMatch { fullMatch, start, end, x, y };
            matches.push_back(newMatch);
        }
    }
    catch (std::regex_error &e) {
        std::cerr << "Regex error: " << e.what() << std::endl;
    }

    return matches;
}

int computeDoAndDont(const vector<Match1> &regex1Matches,
                     const vector<Match2> &regex2Matches)
{
    /*
    for (auto &match : regex1Matches) {
        cout << match.start << "|" << match.end << " [" << match.x << ","
             << match.y << "]" << endl;
    }
    // cout << "allDoDontMatches.size()=" << regex2Matches.size() << endl;
    for (auto &match : regex2Matches) {
        cout << match.start << "|" << match.end << " [" << match.isDo << "]"
             << endl;
    }
    */

    int result { 0 };

    // Add all the beginning mul() before do() | don't()
    int matches1_idx = 0;
    int matches2_idx = 0;

    while (matches1_idx < regex1Matches.size() &&
           regex1Matches[matches1_idx].end <
               regex2Matches[matches2_idx].start) {
        result +=
            (regex1Matches[matches1_idx].x * regex1Matches[matches1_idx].y);
        ++matches1_idx;
    }
    cout << "After all begining: result= " << result << endl;

    // Skip all the matches1 until we are after match2-end
    for (; matches2_idx < regex2Matches.size(); ++matches2_idx) {

        const auto &match2 = regex2Matches[matches2_idx];
        // cout << "curr match2-iter " << match2.start << "|" << match2.end << "
        // ["
        // << match2.isDo << "]" << endl;

        // cout << "curr-match1-start " << regex1Matches[matches1_idx].start <<
        // "|"
        //      << regex1Matches[matches1_idx].end << " ["
        //      << regex1Matches[matches1_idx].x << ","
        //      << regex1Matches[matches1_idx].y << "]" << endl;

        // Skip mul() that are before the do()/don't()
        while (matches1_idx < regex1Matches.size() &&
               match2.end > regex1Matches[matches1_idx].start) {
            ++matches1_idx;
        }
        // cout << "curr-match1-end " << matches1_idx << " "
        //      << regex1Matches[matches1_idx].start << "|"
        //      << regex1Matches[matches1_idx].end << " ["
        //      << regex1Matches[matches1_idx].x << ","
        //      << regex1Matches[matches1_idx].y << "]" << endl;

        if (match2.isDo && matches1_idx < regex1Matches.size()) {
            result +=
                (regex1Matches[matches1_idx].x * regex1Matches[matches1_idx].y);
            ++matches1_idx; // Move to the next match1
        }
    }
    cout << "LINE RESULT = " << result << endl;

    return result;
}

int main()
{
    cout << "DAY-03 part-02" << endl;

    // Read the input file
    std::ifstream file(FILE_PATH);

    // Check if the file is opened correctly
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    // Regular Expression, that match mul(x,y)
    string regularExpression = R"(mul\((\d{1,3}),(\d{1,3})\))";

    string regularExpression2 = R"(do\(\)|don't\(\))";

    string line;

    int result { 0 };

    while (getline(file, line)) {
        // cout << line << endl;

        // Create Pattern Matches
        auto regex1Matches = findRegex1Matches(line, regularExpression);

        auto regex2Matches = findRegex2Matches(line, regularExpression2);

        result += computeDoAndDont(regex1Matches, regex2Matches);
    }
    cout << "RESULT: " << result << endl;
    // 14871649 -> too low

    file.close();

    return 0;
}
