#include "shell.h"

struct Path {
  std::vector<std::string> pathes;
  void show_path(){
    for (int i = 0; i < pathes.size(); i++) {
      std::cout<<pathes[i];
    }
  }
  void add_path(std::string s){
    bool exit = true;
    for (int i = 0; i < pathes.size(); i++) {
      if(pathes[i] == s){
        exit = false;
      }
    }
    if(exit){
      pathes.push_back(s);
    }
      else{
      std::cout<<"That path already exists \n";
    }
  }
  void delete_path(std::string s){
    for (int i = 0; i < pathes.size(); i++) {
      if(pathes[i] == s){
        pathes.erase(pathes.begin() + i,pathes.begin() + i + 1);
        break;
      }
    }
  }
};

std::vector<std::string> parsing (std::string input_line){
  for (int i = 0; i < input_line.size(); i++) {
    if(input_line.at(i) == '|'){
      input_line.insert(i, " ");
      input_line.insert(i + 2, " ");
      i++;
    }
    if(input_line.at(i) == '<'
    && input_line.at(i + 1) != '<'){
        input_line.insert(i, " ");
        input_line.insert(i + 2, " ");
        i++;
    }
    if(input_line.at(i) == '>'
    && input_line.at(i + 1) != '>'){
        input_line.insert(i, " ");
        input_line.insert(i + 2, " ");
        i++;
    }
    if(input_line.at(i) == '>'
    && input_line.at(i + 1) == '>'){
        input_line.insert(i, " ");
        input_line.insert(i + 3, " ");
        i+=2;
    }
    if(input_line.at(i) == '<'
    && input_line.at(i + 1) == '<'){
        input_line.insert(i, " ");
        input_line.insert(i + 3, " ");
        i+=2;
    }
  }
  std::stringstream ss (input_line) ;
  std::vector<std::string> return_value ;
  for ( std::string word; ss>>word;) {
    return_value.push_back(word);
  }
  for (int i = 0; i < return_value.size(); i++) {
    std::cout << return_value[i] << std::endl;
  }
  return return_value;
}


void fork_exec(std::vector<std::string> vector_arg){
    //execvp accepts only an array of string pointers
    const char *program =(vector_arg[0]).c_str();
    const char **arg = new const char* [vector_arg.size()+2];  //extra space for program name and sentinel
    arg [0] = program;
    for (int i = 0;  i < vector_arg.size()+1;  ++i)
            arg [i+1] = (vector_arg[i]).c_str();

    arg [vector_arg.size()+1] = NULL;  // end of arguments sentinel is NULL

    int pid =fork();
    if(pid == -1){
        std::cout << "OH NO :( I am sick, can't do that";
    }
    else if(pid == 0){
        //child
        //exec is execute, 'p': give the name of the program and the operating system will look for the program in the path
        execvp(program, (char **)arg );
    }
    else{
        //parent
          waitpid(pid, NULL, 0);
    }
}

void get_comand(void) {
  std::string input_line;
  std::vector<std::string> parsed_commands;
  std::cout << "[o my gosh shell] $ ";
  getline (std::cin, input_line) ;
  parsed_commands = parsing(input_line);

  fork_exec(parsed_commands);
}
