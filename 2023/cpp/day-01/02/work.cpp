#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

#pragma region Helpers
// Function to print a pair of pairs (size_t, int), (size_t, int)
void print_pairs(const pair<pair<size_t, int>, pair<size_t, int>>& p) {
  cout << "Left-Num:: idx:" << p.first.first << ", num:" << p.first.second
       << endl;
  cout << "Right-Num:: idx:" << p.second.first << ", num:" << p.second.second
       << endl;
}
#pragma endregion

#pragma region Approach-1: Find LeftMost, RightMost - string & number, chose edge most

pair<size_t, int> find_leftmost(string& line, unordered_map<string, int>* map) {
  size_t left_string_idx = string::npos;
  int left_string_digit = -1;

  // Search for all 10 digits represented as text
  for (const auto& pair : *map) {
    string number_str = pair.first;

    size_t idx = line.find(number_str);

    // if there is a sub-string, update the leftmost idx, number
    if (idx != string::npos && idx < left_string_idx) {
      left_string_idx = idx;
      left_string_digit = pair.second;
    }
  }

  return {left_string_idx, left_string_digit};
}

pair<size_t, int> find_rightmost(string& line,
                                 unordered_map<string, int>* map) {
  size_t right_string_idx = string::npos;
  int right_string_digit = -1;

  // Search for all 10 digits represented as text
  for (const auto& pair : *map) {
    string number_str = pair.first;

    size_t idx = line.rfind(number_str);

    // if there is a sub-string, update the rightmost idx, number
    if (idx != string::npos &&
        (right_string_idx == string::npos || idx > right_string_idx)) {
      right_string_idx = idx;
      right_string_digit = pair.second;
    }
  }

  return {right_string_idx, right_string_digit};
}

pair<pair<size_t, int>, pair<size_t, int>> get_leftmost_and_rightmost_digits(
    string line) {
  int left_digit = -1, right_digit = -1;

  // Use two pointers to find the first and last digit
  size_t left_idx = 0, right_idx = line.length() - 1;

  while (left_idx <= right_idx) {
    if (left_digit == -1 && isdigit(line[left_idx])) {
      left_digit = line[left_idx] - '0';
    }
    if (right_digit == -1 && isdigit(line[right_idx])) {
      right_digit = line[right_idx] - '0';
    }
    // Break if both digits are found
    if (left_digit != -1 && right_digit != -1) break;

    if (left_digit == -1) left_idx++;
    if (right_digit == -1) right_idx--;
  }

  // Return the the leftmost, rightmost indexes & digits
  return {{left_idx, left_digit}, {right_idx, right_digit}};
}

int get_calibrated_value_approach_1(string line) {
  // cout << line << endl;

  // Create an unordered_map with string keys and integer values
  unordered_map<string, int> string_num_map = {
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  // Get the first string number from left
  auto leftmost_result = find_leftmost(line, &string_num_map);

  // Get the second digit from right
  auto rightmost_result = find_rightmost(line, &string_num_map);

  // Get the first digit from left & Get the second string number from right
  auto two_digit_num = get_leftmost_and_rightmost_digits(line);

  // print_pairs({leftmost_result, rightmost_result});
  // print_pairs(two_digit_num);

  // Use the most left
  int first_digit = leftmost_result.first != string::npos &&
                            leftmost_result.first < two_digit_num.first.first
                        ? leftmost_result.second
                        : two_digit_num.first.second;

  // Use the most right
  int second_digit = rightmost_result.first != string::npos &&
                             rightmost_result.first > two_digit_num.second.first
                         ? rightmost_result.second
                         : two_digit_num.second.second;

  // Return the two digit number
  int calibrated_number = (first_digit * 10) + second_digit;

  // cout << first_digit << " " << second_digit << endl;
  // cout << calibrated_number << endl;

  return calibrated_number;
}

#pragma endregion

#pragma region Approach-2: Find all digits & their indexes. Sort them by index, get first & last.

int get_calibrated_digit(const string& line,
                         const unordered_map<string, int>& word_map,
                         bool from_left) {
  vector<pair<int, int>> found_digits;

  // Find the numeric digits
  for (int idx = 0; idx < line.length(); idx++) {
    if (isdigit(line[idx])) {
      found_digits.push_back({idx, line[idx] - '0'});
    }
  }

  // Find the word digits
  for (const auto& [digit_word, digit] : word_map) {
    size_t pos = line.find(digit_word);
    // size_t pos = lower_line.find(digit_word);
    while (pos != string::npos) {
      found_digits.push_back({pos, digit});
      pos = line.find(digit_word, pos + 1);
    }
  }

  // No digits founds
  if (found_digits.empty()) return -1;

  // Sort all the found words based on the found index
  sort(found_digits.begin(), found_digits.end());

  return from_left ? found_digits.front().second : found_digits.back().second;
}

int get_calibrated_value_approach_2(string line) {
  // cout << line << endl;

  // Create an unordered_map with string keys and integer values
  unordered_map<string, int> string_num_map = {
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  int left_digit = get_calibrated_digit(line, string_num_map, true);
  int right_digit = get_calibrated_digit(line, string_num_map, false);

  // Return the two digit number
  int calibrated_number = left_digit * 10 + right_digit;

  // cout << first_digit << " " << second_digit << endl;
  // cout << calibrated_number << endl;

  return calibrated_number;
}

#pragma endregion

int main_with_logging() {
  // Read the input file
  // ifstream file("./2023/cpp/day-01/test_input.txt");
  ifstream file("./2023/cpp/day-01/input.txt");

  // Open Log Files, in truncate mode to empty at start
  ofstream log1("./2023/cpp/day-01/log1.log");
  ofstream log2("./2023/cpp/day-01/log2.log");
  ofstream log3("./2023/cpp/day-01/log3.log");

  // Check if the file is opened correctly
  if (!file.is_open()) {
    cerr << "Failed to open file" << endl;
    return -1;
  }

  // Sum of all calibration values
  int total_calibrated_value_1 = 0, total_calibrated_value_2 = 0;

  string line;
  while (getline(file, line)) {
    int calib_val_1, calib_val_2;

    // Approach 1 : 54925
    calib_val_1 = get_calibrated_value_approach_1(line);
    log1 << line << " " << calib_val_1 << endl;

    total_calibrated_value_1 += calib_val_1;

    // Approach 2 : 54925
    calib_val_2 = get_calibrated_value_approach_2(line);
    log2 << line << " " << calib_val_2 << endl;

    if (calib_val_1 != calib_val_2) {
      log3 << line << " " << calib_val_1 << " " << calib_val_2 << endl;
    }

    total_calibrated_value_2 += calib_val_2;
  }

  // Close Log Files
  log1.close();
  log2.close();
  log3.close();

  cout << "Approach-1 Result: " << total_calibrated_value_1 << endl;
  cout << "Approach-2 Result: " << total_calibrated_value_2 << endl;

  return 0;
}

int main_without_logging() {
  // Read the input file
  ifstream file("./2023/cpp/day-01/input.txt");

  // Check if the file is opened correctly
  if (!file.is_open()) {
    cerr << "Failed to open file" << endl;
    return -1;
  }

  // Sum of all calibration values
  int total_calibrated_value_1 = 0, total_calibrated_value_2 = 0;

  string line;
  while (getline(file, line)) {
    int calib_val_1, calib_val_2;

    // Approach 1 : 54925
    calib_val_1 = get_calibrated_value_approach_1(line);
    total_calibrated_value_1 += calib_val_1;

    // Approach 2 : 54925
    calib_val_2 = get_calibrated_value_approach_2(line);
    total_calibrated_value_2 += calib_val_2;
  }

  cout << "Approach-1 Result: " << total_calibrated_value_1 << endl;
  cout << "Approach-2 Result: " << total_calibrated_value_2 << endl;

  return 0;
}
