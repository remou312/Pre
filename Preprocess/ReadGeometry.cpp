#include "ReadGeometry.h"
#include <algorithm>
geoData casData2geoData(const casData& casdata)
{
	geoData geodata;
	return geodata;
}

geoData neuData2geoData(const neuData& neudata)
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
			neudata.points[neudata.cells[i].pointid[0] - 1].coords[0] +
			neudata.points[neudata.cells[i].pointid[1] -1].coords[0] +
			neudata.points[neudata.cells[i].pointid[2] -1].coords[0] +
			neudata.points[neudata.cells[i].pointid[3] -1].coords[0]);
		cell.centroid[1] = 0.25*(
			neudata.points[neudata.cells[i].pointid[0] - 1].coords[1] +
			neudata.points[neudata.cells[i].pointid[1] -1].coords[1] +
			neudata.points[neudata.cells[i].pointid[2] -1].coords[1] +
			neudata.points[neudata.cells[i].pointid[3] -1].coords[1]);
		cell.centroid[2] = 0.25*(
			neudata.points[neudata.cells[i].pointid[0] - 1].coords[2] +
			neudata.points[neudata.cells[i].pointid[1] -1].coords[2] +
			neudata.points[neudata.cells[i].pointid[2] -1].coords[2] +
			neudata.points[neudata.cells[i].pointid[3] -1].coords[2]);
		cell.volume = Volume(neudata.points[neudata.cells[i].pointid[0]-1],
			neudata.points[neudata.cells[i].pointid[1]-1],
			neudata.points[neudata.cells[i].pointid[2]-1],
			neudata.points[neudata.cells[i].pointid[3]-1]);
		geodata.cells.push_back(cell);
	}
	//3.处理单元的面
	//3.1将cell加入到geodata的point中去
	geodata.points = neudata.points;//先将点信息复制过来,目前的cellid是空的
	for (int i = 0; i < neudata.num_cells; i++) {
		for (int j = 0; j < 4; j++) geodata.points[neudata.cells[i].pointid[j]-1].cellid.emplace_back(i);
	}
	//3.2获取单元面的节点信息，存储在暂时的faces中，并创建一个临时cells存储face对应的cell的id
	std::vector<Face_tri> faces;//有重复的
	std::vector<int> cells;
	for (int i = 0; i < neudata.num_cells; i++) {
		Face_tri face1;
		face1.cellid[0] = i + 1;
		face1.cellid[1] = 0;
		face1.pointid[0] = neudata.cells[i].pointid[0];
		face1.pointid[1] = neudata.cells[i].pointid[1];
		face1.pointid[2] = neudata.cells[i].pointid[2];
		faces.push_back(face1);
		cells.push_back(i + 1);
		Face_tri face2;
		face2.cellid[0] = i + 1; face2.cellid[1] = 0;
		face2.pointid[0] = neudata.cells[i].pointid[0];
		face2.pointid[1] = neudata.cells[i].pointid[2];
		face2.pointid[2] = neudata.cells[i].pointid[3];
		faces.push_back(face2);
		cells.push_back(i + 1);
		Face_tri face3;
		face3.cellid[0] = i + 1; face3.cellid[1] = 0;
		face3.pointid[0] = neudata.cells[i].pointid[1];
		face3.pointid[1] = neudata.cells[i].pointid[2];
		face3.pointid[2] = neudata.cells[i].pointid[3];
		faces.push_back(face3);
		cells.push_back(i + 1);
		Face_tri face4;
		face4.cellid[0] = i + 1; face4.cellid[1] = 0;
		face4.pointid[0] = neudata.cells[i].pointid[0];
		face4.pointid[1] = neudata.cells[i].pointid[3];
		face4.pointid[2] = neudata.cells[i].pointid[2];
		faces.push_back(face4);
		cells.push_back(i + 1);
	}
	//3.3处理面信息，去除重复的面
	//3.3.1将面加入到points中
	for (int i = 0; i < faces.size(); i++) {
		int i1 = faces[i].pointid[0];
		int i2 = faces[i].pointid[1];
		int i3 = faces[i].pointid[2];
		geodata.points[i1-1].faceid.emplace_back(i+1);
		geodata.points[i2-1].faceid.emplace_back(i+1);
		geodata.points[i3-1].faceid.emplace_back(i+1);
	}
	//3.3.2去除重复的面
	vector<bool> faceid_used(faces.size(), false);
	for (int i = 0; i < faces.size(); i++) {
		if (faceid_used[i]) continue;
		int i1 = faces[i].pointid[0];
		int i2 = faces[i].pointid[1];
		int i3 = faces[i].pointid[2];
		int ichk = i1 + i2 + i3;
		vector<int> nodes = { i1,i2,i3 };
		for (int j = 0;j<3;j++) {
			for (int k = 0; k < geodata.points[nodes[j] - 1].faceid.size(); k++)
			{
				if (geodata.points[nodes[j] - 1].faceid[k] == i) continue;
				int j1 = faces[geodata.points[nodes[j] - 1].faceid[k]].pointid[0];
				int j2 = faces[geodata.points[nodes[j] - 1].faceid[k]].pointid[1];
				int j3 = faces[geodata.points[nodes[j] - 1].faceid[k]].pointid[2];
				int jchk = j1 + j2 + j3;
				if (jchk == ichk) {
					if(i1==j1 || i1==j2 || i1==j3){
						if(i2==j1 || i2==j2 || i2==j3){
							if(i3==j1 || i3==j2 || i3==j3){
								faceid_used[geodata.points[nodes[j] - 1].faceid[k]-1] = true;
								faceid_used[i] = true;
								faces[i].cellid[1] = faces[geodata.points[nodes[j] - 1].faceid[k]].cellid[0];
								faces[i].sides[1] = faces[geodata.points[nodes[j] - 1].faceid[k]].sides[0];
								//删除第二个面的信息
								cells[geodata.points[nodes[j] - 1].faceid[k]-1] = 0;
								faces[geodata.points[nodes[j] - 1].faceid[k]-1].cellid[0] = 0;
								faces[geodata.points[nodes[j] - 1].faceid[k]-1].sides[0] = 0;
							}
						}
					}
				}
			}
		}
		faceid_used[i] = true;
	}
	//3.4计算面的相关量
	for (int i = 0; i < faces.size(); i++) {
		double coords1[3];
		coords1[0] = geodata.points[faces[i].pointid[0] - 1].coords[0];
		coords1[1] = geodata.points[faces[i].pointid[0] - 1].coords[1];
		coords1[2] = geodata.points[faces[i].pointid[0] - 1].coords[2];
		double coords2[3];
		coords2[0] = geodata.points[faces[i].pointid[1] - 1].coords[0];
		coords2[1] = geodata.points[faces[i].pointid[1] - 1].coords[1];
		coords2[2] = geodata.points[faces[i].pointid[1] - 1].coords[2];
		double coords3[3];
		coords3[0] = geodata.points[faces[i].pointid[2] - 1].coords[0];
		coords3[1] = geodata.points[faces[i].pointid[2] - 1].coords[1];
		coords3[2] = geodata.points[faces[i].pointid[2] - 1].coords[2];
		double normal1 = (coords2[1] - coords1[1]) * (coords3[2] - coords1[2]) - (coords2[2] - coords1[2]) * (coords3[1] - coords1[1]);
		double normal2 = (coords3[1] - coords2[1]) * (coords1[2] - coords2[2]) - (coords3[2] - coords2[2]) * (coords1[1] - coords2[1]);
		double normal3 = (coords1[1] - coords3[1]) * (coords2[2] - coords3[2]) - (coords1[2] - coords3[2]) * (coords2[1] - coords3[1]);
		double area = 0.5 * sqrt(normal1 * normal1 + normal2 * normal2 + normal3 * normal3);
		faces[i].area = area;
		faces[i].normal[0] = normal1;
		faces[i].normal[1] = normal2;
		faces[i].normal[2] = normal3;
		faces[i].centroid[0] = (coords1[0] + coords2[0] + coords3[0]) / 3.0;
		faces[i].centroid[1] = (coords1[1] + coords2[1] + coords3[1]) / 3.0;
		faces[i].centroid[2] = (coords1[2] + coords2[2] + coords3[2]) / 3.0;
	}
	for (int i = 0; i < faces.size(); i++) {
		//方向
	}	
	//3.5将临时面放入geodata中（面的边界属性还未处理）

	//4.处理边界信息
	return geodata;
}

gridData geoData2gridData(const geoData& geodata)
{
	return gridData();
}
