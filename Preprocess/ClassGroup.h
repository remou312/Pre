#pragma once
#include <vector>
struct Point_3d {
    int id;
    double x, y, z;
};
struct Face_tri {
    int id;
    int pointid1, pointid2, pointid3;
    int cellid1, cellid2;
};
struct casData {
    int dim;
    int num_points;
    int num_faces;
    int num_cells;
    std::vector<Point_3d> points;
    std::vector<Face_tri> faces;
};

struct Cell_Tet {
    int id;
    int faceid1, faceid2, faceid3, faceid4;
    int pointid1, pointid2, pointid3, pointid4;
    int Typeid;
    double volume;
    double centroid[3];
};
struct Geo {

};
