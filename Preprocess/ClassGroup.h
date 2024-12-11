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
    int id;
    int Ncell;
    std::vector<int> cellid;
    std::vector<int> celltype;
    std::vector<int> face2cellid;
};
struct cellBnd {
    int id;
    int cellid;
    int faceid;
};
struct faceBnd {
    int id;
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
};
struct mshData {
    int num_cells;
};
struct gridData {
    int dim;
    int num_points;
};
struct datData {
    int dim;
};