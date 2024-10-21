#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Bag {
  int red = 0;
  int blue = 0;
  int green = 0;
  void print() {
    cout << "Red:" << red << " Blue: " << blue << " Green: " << green << endl;
  }
};

struct Game {
  int game_id;
  vector<Bag> all_turns;
  void print() {
    cout << "Game_Id: " << game_id << endl;
    for (Bag bag : all_turns) {
      bag.print();
    }
  };
};

vector<string> split(const string& line, char delimiter) {
  vector<string> result;
  std::stringstream ss(line);
  string token;

  // Use getline to split by the delimiter
  while (std::getline(ss, token, delimiter)) {
    result.push_back(token);
  }
  return result;
}

void count_balls_in_turn(const string& line, Bag* bag) {
  std::istringstream iss(line);
  int number;

  string color_str;
  iss >> number >> color_str;

  if (color_str == "red") {
    bag->red = number;
  } else if (color_str == "green") {
    bag->green = number;
  } else if (color_str == "blue") {
    bag->blue = number;
  }
}

void covert_turn_to_bag(string turn, Bag* bag) {
  vector<string> color_counts = split(turn, ',');
  for (int idx = 0; idx < color_counts.size(); idx++) {
    string cc = color_counts[idx];
    count_balls_in_turn(cc, bag);
  }
}

Game convert_to_game(const string& line) {
  Game game;

  size_t start = 5;
  size_t end = line.find(':');
  string game_id_str = line.substr(start, end - start);

  game.game_id = std::stoi(game_id_str);

  vector<string> turns = split(line.substr(end + 1, line.length()), ';');
  for (int idx = 0; idx < turns.size(); idx++) {
    Bag bag;
    covert_turn_to_bag(turns[idx], &bag);
    game.all_turns.push_back(bag);
  }
  return game;
}

bool validate_game(Game* game) {
  // Allowed count
  int RED = 12, BLUE = 14, GREEN = 13;

  // Evaluate all turns
  for (Bag bag : game->all_turns) {
    if (bag.red > RED || bag.blue > BLUE || bag.green > GREEN) {
      return false;
    }
  }

  return true;
}

int get_power(Game* game) {
  int red = 0, blue = 0, green = 0;
  // 4, 2, 6

  for (Bag bag : game->all_turns) {
    red = std::max(bag.red, red);
    blue = std::max(bag.blue, blue);
    green = std::max(bag.green, green);
  }

  int result = red * green * blue;
  cout << "result: " << result << endl;
  return result;
}

int main() {
  /*
  string test =
      "Game 54: 13 blue, 8 green; 15 blue, 3 red, 7 green; 8 green, 1 blue; 8 "
      "blue, 3 red, 6 green; 3 red, 1 green, 12 blue; 9 green, 3 red, 2 blue";
  cout << test << endl;
  Game game = convert_to_game(test);
  game.print();
  */

  // Read the input file
  std::ifstream file("./2023/cpp/day-02/input.txt");

  // Check if the file is opened correctly
  if (!file.is_open()) {
    cout << "Failed to open file" << endl;
    return -1;
  }

  // Sum of all calibration values
  int result = 0;

  string line;
  while (getline(file, line)) {
    int calib_val;

    Game game = convert_to_game(line);
    if (validate_game(&game)) {
      // result += game.game_id;
      result += get_power(&game);
    }
  }

  cout << "Result: " << result << endl;
  return 0;
}