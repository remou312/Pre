#pragma once
#include "ClassGroup.h"
#include <regex>
#include "SplitCas.h"
using namespace std;
casData readCase(std::ifstream& casfile);
neuData readNeu(std::ifstream& neufile);