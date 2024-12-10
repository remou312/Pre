#pragma once
#include <vector>
struct Point_3d {
    int id;
    double x, y, z;
    double vector[3]={x,y,z};
    std::vector<int>cellid;
    std::vector<int>faceid;
};
struct Face_tri {
    int id;
    int pointid1, pointid2, pointid3;
    int cellid1, cellid2;
    std::vector<int>cellid={pointid1,pointid2,pointid3};
    std::vector<int>pointid={cellid1,cellid2};
    std::vector<int>sides;
};
struct Cell_Tet {
    int id;
    int Typeid;
    int pointid1, pointid2, pointid3, pointid4;
    std::vector<int> pointid={pointid1,pointid2,pointid3,pointid4};
    int faceid1, faceid2, faceid3, faceid4;
    std::vector<int> faceid={faceid1,faceid2,faceid3,faceid4};
    double volume;
    double centroid[3];
};
struct bnd {
    int id;
    int Ncell;
    std::vector<int> cellid;
    std::vector<int> celltype;
    std::vector<int> face2cellid;
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
    std::vector<bnd> bnds;
};
struct geoData {
    double scale=1.0;
    int num_points;
    int num_faces;
    int num_cells;
    std::vector<Point_3d> points;
    std::vector<Face_tri> faces;
    std::vector<Cell_Tet> cells;
};