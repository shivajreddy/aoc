#include "day3.h"

bool find_two_numbers(const string& prev_line, const string& curr_line,
                      const string& next_line) {
  // Current line must not be empty
  if (curr_line.empty()) return false;

  vector<int> valid_part_numbers = {};
  int sum_of_part_numbers = 0;
  string temp;
  bool is_valid_number = false;

  cout << "hi" << endl;
  return false;
}

// Day-03 Part-02
int main() {
  // Read the input file
  std::ifstream file("./2023/cpp/day-03/test_input.txt");
  // std::ifstream file("./2023/cpp/day-03/input.txt");

  int result = 0;
  string prev = "", curr = "", next = "";

  while (std::getline(file, next)) {
    find_two_numbers(prev, curr, next);
    // Update lines
    prev = curr;
    curr = next;
  }
  // Capture last line
  next = "";
  // result += valid_number(prev, curr, next);

  cout << "Result: " << result << endl;

  return 0;
}