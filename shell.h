#pragma once
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unordered_map>
#include <stdio.h>
#include <cstring>

const char ** hash_char();
void get_comand(void);
std::vector <std::string> parasing (std::string inputLine);
void add_spaces(std::string input_line, size_t& pos1, size_t pos2);
struct Path;
