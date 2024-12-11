#pragma once
#include <vector>
struct Point_3d {
    int id;
    double coords[3];
    std::vector<int>cellid;
    std::vector<int>faceid;
};
struct Face_tri {
    int id;
    double area;
    double centroid[3];
    double normal[3];
    int cellid[2];
    int pointid[3];
    int sides[2];
    int bndid;
    double lambda;
};
struct Cell_Tet {
    int id;
    double volume;
    int Typeid;
    int pointid[4];
    std::vector<int>faceid;
    double centroid[3];
};
struct Bnd {
    //这是region形式的边界，包含有多个cell，对于每个cell，face2cellid记录了cell四个面的哪个面是边界面
    int id;
    int Ncell;
    std::vector<int> cellid;
    std::vector<int> celltype;
    std::vector<int> face2cellid;
};
struct cellBnd {
    //这是cell形式的边界，本质上是一个cell，记录着cell的（重排）id，以及cell的四个点，以及属于的Bnd的id（rid）
    int id;//cell的重排id
    int points[4];
    int rid;
    int cellid;//cell的id
    int faceid;
};
struct faceBnd {
    //这是face形式的边界，本质上是一个face，记录着face的id，以及属于的Bnd的id（rid）
    int id;
    int rid;
    int faceid;
};
struct casData {
    int dim;
    int num_points;
    int num_faces;
    int num_cells;
    std::vector<Point_3d> points;
    std::vector<Face_tri> faces;
};
struct neuData {
    int dim;
    int num_points;
    int num_cells;
    std::vector<Point_3d> points;
    std::vector<Cell_Tet> cells;
    std::vector<Bnd> bnds;
};
struct geoData {
    double scale=1.0;
    int num_points;
    int num_faces;
    int num_cells;
    std::vector<Point_3d> points;
    std::vector<Face_tri> faces;
    std::vector<Cell_Tet> cells;
    std::vector<faceBnd>facebnds;
    std::vector<cellBnd>cellbnds;
};
struct mshData {
    double scale = 1.0;
    int num_points;
    int num_faces;
    int num_cells;
    std::vector<Point_3d> points;
    std::vector<Face_tri> faces;
    std::vector<Cell_Tet> cells;
    std::vector<faceBnd>facebnds;
    std::vector<cellBnd>cellbnds;
};
struct gridData {
    int dim;
    int num_points;
};
struct datData {
    int dim;
};