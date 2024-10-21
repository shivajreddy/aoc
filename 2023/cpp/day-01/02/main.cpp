#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int get_digit(const string& line, const unordered_map<string, int>& word_map,
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

int get_calibrated_value(string line) {
  // Create an unordered_map with string keys and integer values
  unordered_map<string, int> string_num_map = {
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  int left_digit = get_digit(line, string_num_map, true);
  int right_digit = get_digit(line, string_num_map, false);

  // Return the two digit number
  int calibrated_number = (left_digit * 10) + right_digit;

  return calibrated_number;
}

int day_01_part_02_main() {
  // Read the input file
  ifstream file("./2023/cpp/day-01/input.txt");

  // Check if the file is opened correctly
  if (!file.is_open()) {
    cerr << "Failed to open file" << endl;
    return -1;
  }

  // Sum of all calibration values
  int total_calibrated_value = 0;

  string line;
  while (getline(file, line)) {
    int calib_val;

    calib_val = get_calibrated_value(line);
    total_calibrated_value += calib_val;
  }

  cout << "Result: " << total_calibrated_value << endl;

  return 0;
}
