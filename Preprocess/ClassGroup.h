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
    //����region��ʽ�ı߽磬�����ж��cell������ÿ��cell��face2cellid��¼��cell�ĸ�����ĸ����Ǳ߽���
    int id;
    int Ncell;
    std::vector<int> cellid;
    std::vector<int> celltype;
    std::vector<int> face2cellid;
};
struct cellBnd {
    //����cell��ʽ�ı߽磬��������һ��cell����¼��cell�ģ����ţ�id���Լ�cell���ĸ��㣬�Լ����ڵ�Bnd��id��rid��
    int id;//cell������id
    int points[4];
    int rid;
    int cellid;//cell��id
    int faceid;
};
struct faceBnd {
    //����face��ʽ�ı߽磬��������һ��face����¼��face��id���Լ����ڵ�Bnd��id��rid��
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