#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
std::ifstream openFile(const std::string& extension);
std::ifstream openCasFile();
std::ifstream openNeuFile();
std::ifstream openMshFile();