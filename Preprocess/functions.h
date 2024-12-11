#pragma once
#include "ClassGroup.h"
#include <cmath>
double Volume(const Point_3d& p1, const Point_3d& p2, const Point_3d& p3, const Point_3d& p4);
void normalise(double a[3]);//由于数组的特殊性，本质上是引用传递，所以不需要返回值