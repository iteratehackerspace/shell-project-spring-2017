#include "shell.h"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;
using std::unordered_map;
using std::memcpy;
        
unordered_map<string, string> env = {
    ///this is just for try... instead of leaving it empty...
    {"RED","#FF0000"},
    {"GREEN","#00FF00"},
    {"BLUE","#0000FF"}
    };
 

const char ** hash_char(){
    const char **envv= new const char* [env.size()+1];
    
    int i=0;
    for( const auto& n : env ) {
        envv[i]=new char[(n.first + "=" + n.second).size()]; 
        memcpy(envv+i, (n.first + "=" + n.second).c_str(),(n.first + "=" + n.second).size() +1);
        i++;
    }
    envv[i]=NULL;
    return envv;
} 

struct Path {
  vector<string> paths;
  void show_path(){
    for (size_t i = 0; i < paths.size(); i++) {
      cout<<paths[i];
    }
  }
  void add_path(string path){
    bool shouldAdd = true;
    for (size_t i = 0; i < paths.size(); i++) {
      if(paths[i] == path){
        shouldAdd = false;
      }
    }
    if(shouldAdd){
      paths.push_back(path);
    }
    else{
      cout<<"The path already exists \n";
    }
  }
  void delete_path(string path){
    for (size_t i = 0; i < paths.size(); i++) {
      if(paths[i] == path){
        paths.erase(paths.begin() + i,paths.begin() + i + 1);
        break;
      }
    }
  }
};

vector<string> parsing (string input_line){
  for (size_t i = 0; i < input_line.size(); i++) {
    if(input_line.at(i) == '|'){
      add_spaces(input_line, i, i + 2);
    }
    if(input_line.at(i) == '<'
    && input_line.at(i + 1) != '<'){
      add_spaces(input_line, i, i + 2);
    }
    if(input_line.at(i) == '>'
    && input_line.at(i + 1) != '>'){
      add_spaces(input_line, i, i + 2);
    }
    if(input_line.at(i) == '>'
    && input_line.at(i + 1) == '>'){
      add_spaces(input_line, i, i + 3);
    }
    if(input_line.at(i) == '<'
    && input_line.at(i + 1) == '<'){
      add_spaces(input_line, i, i + 3);
    }
  }
  stringstream ss (input_line) ;
  vector<string> return_value ;
  for (string word; ss>>word;) {
    return_value.push_back(word);
  }
  for (size_t i = 0; i < return_value.size(); i++) {
    cout << return_value[i] << endl;
  }
  return return_value;
}

void add_spaces(string input_line, size_t& pos1, size_t pos2) {
    input_line.insert(pos1, " ");
    input_line.insert(pos2, " ");
    pos1 = pos2 - pos1 - 1;
}

void fork_exec(vector<string> vector_arg){
    //execve accepts only an array of string pointers
    const char *program =(vector_arg[0]).c_str();
    const char **arg = new const char* [vector_arg.size()+2];  //extra space for program name and sentinel
    arg [0] = program;
    for (size_t i = 0;  i < vector_arg.size()+1;  ++i){
        arg [i+1] = new char[vector_arg[i].size()];
        arg [i+1] = (vector_arg[i]).c_str();
        
        //make the next command gives no makefile error then uncomment the previous command 
        //memcpy(arg + i + 1, (vector_arg[i]).c_str(), (vector_arg[i]).size()+1);
    }
  
    arg [vector_arg.size()+1] = NULL;  // end of arguments sentinel is NULL

    int pid =fork();
    if(pid == -1){
        cout << "OH NO :( I am sick, can't do that";
    }
    else if(pid == 0){
        //child
        //exec is execute
        const char** environment=hash_char();
        execve(program, (char **)arg, (char **)environment);
    }
    else{
        //parent
          waitpid(pid, NULL, 0);
    }
}

void get_comand(void) {
  string input_line;
  vector<string> parsed_commands;
  cout << "[oh my gosh shell] $ ";
  getline (cin, input_line) ;
  parsed_commands = parsing(input_line);

  fork_exec(parsed_commands);
  
}