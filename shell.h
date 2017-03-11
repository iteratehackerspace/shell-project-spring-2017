#pragma once
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>

void get_comand(void);
std::vector <std::string> parasing (std::string inputLine);
struct Path;
