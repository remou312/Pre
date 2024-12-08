#pragma once
#include "ClassGroup.h"
#include <regex>
#include "SplitCas.h"
using namespace std;
casData readCas(std::ifstream& casfile);
neuData readNeu(std::ifstream& neufile);