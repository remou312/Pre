#include "functions.h"

double Volume(const Point_3d& p1, const Point_3d& p2, const Point_3d& p3, const Point_3d& p4)
{
    // 计算向量
    double x1 = p2.x - p1.x;
    double y1 = p2.y - p1.y;
    double z1 = p2.z - p1.z;

    double x2 = p3.x - p1.x;
    double y2 = p3.y - p1.y;
    double z2 = p3.z - p1.z;

    double x3 = p4.x - p1.x;
    double y3 = p4.y - p1.y;
    double z3 = p4.z - p1.z;

    // 计算叉积
    double cx = y2 * z3 - z2 * y3;
    double cy = z2 * x3 - x2 * z3;
    double cz = x2 * y3 - y2 * x3;

    // 计算点积
    double dot_product = x1 * cx + y1 * cy + z1 * cz;

    // 返回四面体体积
    return std::abs(dot_product) / 6.0;
}
