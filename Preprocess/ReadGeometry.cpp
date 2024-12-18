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
		int ip = faces[i].cellid[0];
		if (ip > 0) {
			double a[3] ={faces[i].centroid[0]-geodata.cells[ip-1].centroid[0],
				faces[i].centroid[1]-geodata.cells[ip-1].centroid[1],
				faces[i].centroid[2]-geodata.cells[ip-1].centroid[2]};
			double b[3] ={faces[i].normal[0],faces[i].normal[1],faces[i].normal[2]};
			normalise(a);normalise(b);
			double dotp = dot_product(a,b);
			dotp = min(dotp,1.0);
			dotp = max(dotp,-1.0);
			double angle = acos(dotp)*180.0/3.14159265358979323846;
			if (angle > 90.0 && angle < 270.0) {
				faces[i].normal[0] = -faces[i].normal[0];
				faces[i].normal[1] = -faces[i].normal[1];
				faces[i].normal[2] = -faces[i].normal[2];
			}
		}
	}

	//3.5将临时面放入geodata中（面的边界属性还未处理）
	int icnt = 0;
	for (int i = 0; i < faces.size(); i++) {
		if (faces[i].cellid[0] > 0) {
			geodata.faces.push_back(faces[i]);
			geodata.faces[icnt].bndid = 0;
			geodata.faces[icnt].lambda = -1.0;
			icnt++;
		}
	}
	//3.6将face加入到cell中去
	for (int i = 0; i < geodata.faces.size(); i++) {
		geodata.cells[geodata.faces[i].cellid[0] -1].faceid.emplace_back(i+1);
		if (geodata.faces[i].cellid[1] > 0) geodata.cells[geodata.faces[i].cellid[1] -1].faceid.emplace_back(i+1);
	}
	//4.处理边界信息
	//4.1从neudata中获取边界信息，将其放入cellbnds中，属性有cellid,points,rid
	std::vector<cellBnd> cellbnds;
	for (int i = 0; i < neudata.regions.size(); i++) {
		for (int j = 0; j < neudata.regions[i].cellid.size(); j++) {
			cellBnd cellbnd;
			cellbnd.cellid = neudata.regions[i].cellid[j];
			cellbnd.points[0] = neudata.cells[bnd.cellid - 1].pointid[0];
			cellbnd.points[1] = neudata.cells[bnd.cellid - 1].pointid[1];
			cellbnd.points[2] = neudata.cells[bnd.cellid - 1].pointid[2];
			cellbnd.points[3] = neudata.cells[bnd.cellid - 1].pointid[3];
			cellbnd.rid = neudata.regions[i].rid;
			cellbnds.push_back(cellbnd);
		}
	}
	//4.2将cellbnds放入geodata中，并添加一些额外属性。geodata需要facebnd属性，具体来说，需要重编id，faceid，vertexid，rid，distance
	//4.2.1从geodata.faces中获取总边界面数，面的第二个cell编号为0，则为边界面
	for(int i=0;i<geodata.faces.size();i++){
		if(geodata.faces[i].cellid[1]==0){
			int i1 = geodata.faces[i].pointid[0];
			int i2 = geodata.faces[i].pointid[1];
			int i3 = geodata.faces[i].pointid[2];
			int i4 = geodata.faces[i].pointid[3];
			int icnk = 0;










	return geodata;
}

gridData geoData2gridData(const geoData& geodata)
{
	return gridData();
}
