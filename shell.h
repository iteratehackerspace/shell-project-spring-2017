#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>

extern std::string cmd;
extern int status;
void get_command(void);
std::vector <std::string> preasing (std::string inputLine);
int get_status(void);