#include "shell.h"

int status = 0;

std::vector <std::string> parsing (std::string input_line) {
  if (input_line == "ls") {
    status = 1;
  }
  else if (input_line == "clear")
  {
    status = 2;
  }
  else {
  for (int i = 0; i < input_line.size(); i++) {
    if(input_line.at(i) == '<'
    || input_line.at(i) == '>'
    || input_line.at(i) == '|'){
      input_line.insert(i, " ");
      input_line.insert(i + 2, " ");
      i++;
    }
  }
  }
  std::stringstream ss (input_line) ;
  std::vector<std::string> return_value ;
  for ( std::string word; ss>>word;) {
    return_value.push_back(word);
  }
  for (int i = 0; i < return_value.size(); i++) {
    std::cout << "command: " << return_value[i] << std::endl;
  }
  return return_value;
}

void get_command(void) {
  std::string input_line;
  std::vector <std::string> praserd_commands;
  getline (std::cin, input_line) ;
  praserd_commands = parsing(input_line);
}

int get_status(void) {
  return status;
}
