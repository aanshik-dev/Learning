#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string read_line() {
  string buffer;
  getline(cin, buffer);
  return buffer;
}

vector<string> split_line(string line) {
  cout << "inside split_line\n";
  vector<string> tokens;
  stringstream ss(line);
  string token;
  while (ss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

int exit(vector<string> args) {
  return 0;
}

int cat(vector<string> args) {
  if (args.size() < 2) {
    cout << "Too few arguments" << endl;
    return 1;
  } else if (args.size() > 2) {
    cout << "Too many arguments" << endl;
    return 1;
  }

  const string file_path = args[1];
  ifstream file(file_path);
  if (!file.is_open()) {
    cerr << "Error Permission Denied \"Tere fufe ki file nahi hai jo khol lega.\"" << file_path << endl;
    return 1;
  }
  string line;
  while (getline(file, line)) {
    cout << line << endl;
  }
  file.close();
  return 0;
}

int execute(vector<string> args) {
  cout << "inside execute\n";
  if (args.empty()) {
    return 1;
  } else {
    string command_list[] = {"cat", "exit"};
    for (int i = 0; i < command_list->size(); i++) {
      if (args[0] == command_list[i]) {
        switch (1) {
        case 0:
          return cat(args);
        case 1:
          return exit(args);
        default:
          return 1;
        }
      }
    }
  }
  return 0;
}

void loop() {
  while (true) {
    cout << "Hello" << endl;
    cout.flush();

    string line = read_line();
    vector<string> args = split_line(line);

    int status = execute(args);
  }
}

int main() {
  loop();
  return 0;
}