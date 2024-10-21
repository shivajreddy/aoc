#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void print_numbers(const vector<int>* nums);

bool check_around(size_t idx, const string& prev_line, const string& curr_line,
                  const string& next_line);
