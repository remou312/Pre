#include "functions.h"

double Volume(const Point_3d& p1, const Point_3d& p2, const Point_3d& p3, const Point_3d& p4)
{
    // 计算向量
    double vector1[3] = { p2.coords[0] - p1.coords[0], p2.coords[1] - p1.coords[1], p2.coords[2] - p1.coords[2] };
    double vector2[3] = { p3.coords[0] - p1.coords[0], p3.coords[1] - p1.coords[1], p3.coords[2] - p1.coords[2] };
    double vector3[3] = { p4.coords[0] - p1.coords[0], p4.coords[1] - p1.coords[1], p4.coords[2] - p1.coords[2] };

    // 计算叉积
    double cx = vector2[1] * vector3[2] - vector2[2] * vector3[1];
    double cy = vector2[2] * vector3[0] - vector2[0] * vector3[2];
    double cz = vector2[0] * vector3[1] - vector2[1] * vector3[0];

    // 计算点积
    double dot_product = vector1[0] * cx + vector1[1] * cy + vector1[2] * cz;

    // 返回四面体体积
    return std::abs(dot_product) / 6.0;
}
