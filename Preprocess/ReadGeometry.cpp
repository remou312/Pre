#include "ReadGeometry.h"
#include <algorithm>
geoData casdata2geoData(const casData& casdata)
{
	geoData geodata;
	return geodata;
}

geoData neudata2geoData(const neuData& neudata)
{
	geoData geodata;
	//1.先输入比例
	cout << "请输入比例(1.0)：" << endl;
	cin >> geodata.scale;
	//2.读取节点(id,Typeid,centroid,volume)
	geodata.num_cells = neudata.num_cells;
	Cell_Tet cell;
	int id = 0;
	for (int i = 0; i < neudata.num_cells; i++) {
		cell.id = neudata.cells[i].id;
		cell.Typeid = neudata.cells[i].Typeid;
		cell.centroid[0] = 0.25*(
			neudata.points[neudata.cells[i].pointid1-1].x+
			neudata.points[neudata.cells[i].pointid2-1].x+
			neudata.points[neudata.cells[i].pointid3-1].x+
			neudata.points[neudata.cells[i].pointid4-1].x);
		cell.centroid[1] = 0.25*(
			neudata.points[neudata.cells[i].pointid1-1].y+
			neudata.points[neudata.cells[i].pointid2-1].y+
			neudata.points[neudata.cells[i].pointid3-1].y+
			neudata.points[neudata.cells[i].pointid4-1].y);
		cell.centroid[2] = 0.25*(
			neudata.points[neudata.cells[i].pointid1-1].z+
			neudata.points[neudata.cells[i].pointid2-1].z+
			neudata.points[neudata.cells[i].pointid3-1].z+
			neudata.points[neudata.cells[i].pointid4-1].z);
		cell.volume = Volume(neudata.points[neudata.cells[i].pointid1-1],
			neudata.points[neudata.cells[i].pointid2-1],
			neudata.points[neudata.cells[i].pointid3-1],
			neudata.points[neudata.cells[i].pointid4-1]);
		geodata.cells.push_back(cell);
	}
	//3.处理单元的面
	//3.1将cell加入到geodata的point中去
	geodata.points = neudata.points;//先将点信息复制过来,目前的cellid是空的
	for (int i = 0; i < neudata.num_cells; i++) {
		for (int j = 0; j < 4; j++) geodata.points[neudata.cells[i].pointid[j]-1].cellid.emplace_back(i);
	}
	//3.2获取单元面的节点信息，存储在暂时的faces中
	std::vector<Face_tri> faces;//有重复的
	for (int i = 0; i < neudata.num_cells; i++) {
			Face_tri face1;
			face1.cellid = { i + 1,0 };
			face1.pointid.push_back(neudata.cells[i].pointid1);
			face1.pointid.push_back(neudata.cells[i].pointid2);
			face1.pointid.push_back(neudata.cells[i].pointid3);
			face1.sides = { 1,0 };
			faces.push_back(face1);
			Face_tri face2;
			face2.cellid = { i + 1,0 };
			face2.pointid.push_back(neudata.cells[i].pointid1);
			face2.pointid.push_back(neudata.cells[i].pointid2);
			face2.pointid.push_back(neudata.cells[i].pointid4);
			face2.sides = { 3,0 };
			faces.push_back(face2);
			Face_tri face3;
			face3.cellid = { i + 1,0 };
			face3.pointid.push_back(neudata.cells[i].pointid1);
			face3.pointid.push_back(neudata.cells[i].pointid4);
			face3.pointid.push_back(neudata.cells[i].pointid3);
			face3.sides = { 5,0 };
			faces.push_back(face3);
			Face_tri face4;
			face4.cellid={i+1,0};
			face4.pointid.push_back(neudata.cells[i].pointid2);
			face4.pointid.push_back(neudata.cells[i].pointid3);
			face4.pointid.push_back(neudata.cells[i].pointid4);
			face4.sides = { 6,0 };
			faces.push_back(face4);		
		}
	//3.3处理面信息，去除重复的面
	//3.3.1将面加入到geodata的points中
	for (int i = 0; i < faces.size(); i++) {
		int i1 = faces[i].pointid[0];
		int i2 = faces[i].pointid[1];
		int i3 = faces[i].pointid[2];
		geodata.points[i1-1].faceid.emplace_back(i);
		geodata.points[i2-1].faceid.emplace_back(i);
		geodata.points[i3-1].faceid.emplace_back(i);
	}
	//3.3.2去除重复的面
	vector<bool> faceid_used(faces.size(), false);
	for (int i = 0; i < faces.size(); i++) {
		int i1 = faces[i].pointid[0];
		int i2 = faces[i].pointid[1];
		int i3 = faces[i].pointid[2];
		int ichk = i1 + i2 + i3;
		vector<int> nodes = { i1,i2,i3 };
		for (int j = 0;j<3;j++) {
			int ix = nodes[j];
	}


    //3.3将面的信息加入到cell中去

	return geodata;
}