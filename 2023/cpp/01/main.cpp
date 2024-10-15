// https://adventofcode.com/2023/day/1
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Expeccts atleast 1 digit to be there in the given line
int get_two_digit_number(string& line) {
  int first_digit = -1, second_digit = -1;

  int l = 0, r = line.length() - 1;

  // Use two pointers to find the first and last digit
  while (l <= r) {
    if (first_digit == -1 && isdigit(line[l])) {
      first_digit = line[l] - '0';
    }
    if (second_digit == -1 && isdigit(line[r])) {
      second_digit = line[r] - '0';
    }
    // Break if both digits are found
    if (first_digit != -1 && second_digit != -1) break;

    if (first_digit == -1) l++;
    if (second_digit == -1) r--;
  }

  return first_digit * 10 + second_digit;
}

int main() {
  // /* Testing
  string test_line = "btr4seventhree7hbkkg";
  cout << get_two_digit_number(test_line) << endl;
  // */

  // /*
  // Read the input file
  ifstream file("./2023/cpp/01/input.txt");

  // Check if the file is opened correctly
  if (!file.is_open()) {
    cerr << "Failed to open file" << endl;
    return -1;
  }

  int result = 0;

  string line;
  while (getline(file, line)) {
    result += get_two_digit_number(line);
  }
  cout << "Result: " << result << endl;

  return 0;
  // */
}
