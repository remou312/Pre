#pragma once
#include "ClassGroup.h"
#include <iostream>
#include "Functions.h"
#include <numeric>
using namespace std;
geoData casData2geoData(const casData& casdata);
geoData neuData2geoData(const neuData& neudata);
gridData geoData2gridData(const geoData& geodata);