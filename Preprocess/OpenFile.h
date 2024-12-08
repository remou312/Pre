#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
extern std::string filename;
namespace fs = std::filesystem;
std::ifstream openCasFile();
//std::ifstream openMshFile();