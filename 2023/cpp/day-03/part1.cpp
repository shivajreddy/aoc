#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#pragma region Helpers
void print_numbers(const vector<int>* nums) {
  if (nums == nullptr || nums->empty()) return;
  cout << "nums: ";
  for (size_t i = 0; i < nums->size(); i++) {
    cout << (*nums)[i] << " ";
  }
  cout << endl;
}

#pragma endregion

bool check_around_claude(size_t idx, const std::string& prev_line,
                         const std::string& curr_line,
                         const std::string& next_line) {
  const std::vector<std::string> lines = {prev_line, curr_line, next_line};
  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      if (dy == 0 && dx == 0) continue;
      int y = 1 + dy;
      int x = idx + dx;
      if (y >= 0 && y < lines.size() && x >= 0 && x < lines[y].size()) {
        char c = lines[y][x];
        if (c != '.' && !std::isdigit(c)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool check_around(size_t idx, const string& prev_line, const string& curr_line,
                  const string& next_line) {
  char target_char;

  // top
  if (prev_line != "") {
    target_char = prev_line[idx];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  // bot
  if (next_line != "") {
    target_char = next_line[idx];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  // left
  if (idx != 0) {
    target_char = curr_line[idx - 1];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  // top-left
  if (prev_line != "" && idx != 0) {
    target_char = prev_line[idx - 1];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  // bot-left
  if (next_line != "" && idx != 0) {
    target_char = next_line[idx - 1];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  // right
  if (idx + 1 <= curr_line.size() - 1) {
    target_char = curr_line[idx + 1];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  // top-right
  if (prev_line != "" && idx + 1 <= prev_line.size() - 1) {
    target_char = prev_line[idx + 1];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  // bot-right
  if (next_line != "" && idx + 1 <= next_line.size() - 1) {
    target_char = next_line[idx + 1];
    if (target_char != '.' && !isdigit(target_char)) {
      return true;
    }
  }

  return false;
}

int valid_number(const string& prev_line, const string& curr_line,
                 const string& next_line) {
  // Current line must not be empty
  if (curr_line.empty()) return 0;

  // vector<int> valid_part_numbers = {};
  int sum_of_part_numbers = 0;
  string temp;
  bool is_valid_number = false;

  // Check prev & next, if only they exist
  for (size_t idx = 0; idx <= curr_line.size(); ++idx) {
    char curr_char = curr_line[idx];
    if (isdigit(curr_char)) {
      temp += curr_char;

      // Look around only if not already valid
      if (!is_valid_number) {
        // Check if number is valid
        if (check_around(idx, prev_line, curr_line, next_line)) {
          is_valid_number = true;
        }
      }

    } else if (!temp.empty()) {
      int num = std::stoi(temp);
      // cout << "checking " << num << endl;

      // Verify if this number is valid
      if (is_valid_number) {
        // cout << "VALID :) " << endl;
        // valid_part_numbers.push_back(num);
        sum_of_part_numbers += num;
      }
      temp.clear();
      is_valid_number = false;  // reset the flag
    }
  }

  // print_numbers(&valid_part_numbers);
  //  cout << "sum : " << sum_of_part_numbers << endl;

  // cout << endl;
  return sum_of_part_numbers;
}

// Day-03 Part-01
int day_03_part_01() {
  // Read the input file
  // std::ifstream file("./2023/cpp/day-03/test_input.txt");
  std::ifstream file("./2023/cpp/day-03/input.txt");

  int result = 0;
  string prev = "", curr = "", next = "";

  while (std::getline(file, next)) {
    result += valid_number(prev, curr, next);

    // Update lines
    prev = curr;
    curr = next;
  }
  // Capture last line
  next = "";
  result += valid_number(prev, curr, next);

  cout << "Result: " << result << endl;

  return 0;
}