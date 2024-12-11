#include "ReadFile.h"
casData readCas(std::ifstream& casfile) {
    std::vector<std::string> blocks = splitCas(casfile);
    casData casdata;
    //从blocks中解析信息
    for (int i = 0; i < blocks.size(); i++)
    {
        //检测维度
        if (blocks[i].substr(0, 2) == "(2") {
            casdata.dim = blocks[i][3] - '0';
            cout << "Dimension: " << casdata.dim << endl;
        }
        //检测节点数
        if (blocks[i].substr(0, 9) == "(10 (0 1 ") {
            std::string subStr = blocks[i].substr(9); // 从第10个字符开始提取剩下的字符串
            size_t pos = subStr.find(' '); // 查找第一个空格的位置

            if (pos != std::string::npos) {
                subStr = subStr.substr(0, pos); // 提取从开始到第一个空格的子字符串
            }
            cout << "NNode: " << subStr << endl;
            casdata.num_points = stoi(subStr, nullptr, 16);
            cout << "NNode: " << casdata.num_points << endl;
        }
        //检测面数
        if (blocks[i].substr(0, 9) == "(13 (0 1 ") {
            std::string subStr = blocks[i].substr(9);
            size_t pos = subStr.find(' '); // 查找第一个空格的位置

            if (pos != std::string::npos) {
                subStr = subStr.substr(0, pos); // 提取从开始到第一个空格的子字符串
            }
            cout << "NFace: " << subStr << endl;
            casdata.num_faces = stoi(subStr, nullptr, 16);
            cout << "NFace: " << casdata.num_faces << endl;
        }
        //检测单元数
        if (blocks[i].substr(0, 9) == "(12 (0 1 ") {
            std::string subStr = blocks[i].substr(9);
            size_t pos = subStr.find(' '); // 查找第一个空格的位置

            if (pos != std::string::npos) {
                subStr = subStr.substr(0, pos); // 提取从开始到第一个空格的子字符串
            }
            cout << "NCell: " << subStr << endl;
            casdata.num_cells = stoi(subStr, nullptr, 16);
            cout << "NCell: " << casdata.num_cells << endl;
        }
        //读取节点坐标
        if (blocks[i].substr(0, 5) == "(10 (" && blocks[i].substr(5, 1) != "0") {
            // 假设 blocks[i] 为整个数据块，可以按行分割
            std::istringstream blockStream(blocks[i]);
            std::string line;
            // 先读取并忽略第一行
            std::getline(blockStream, line);
            // 然后读取剩下的内容
            while (std::getline(blockStream, line)) {
                // 确保读取的行不是最后一行
                if (line != "))") {
                    Point_3d point;
                    std::istringstream lineStream(line);
                    lineStream >> point.coords[0] >> point.coords[1] >> point.coords[2];
                    point.id = casdata.points.size() + 1;
                    casdata.points.emplace_back(point);
                }
            }
        }
        //读取面信息
        if (blocks[i].substr(0, 5) == "(13 (" && blocks[i].substr(5, 1) != "0") {
            // 假设 blocks[i] 为整个数据块，可以按行分割
            std::istringstream blockStream(blocks[i]);
            std::string line;
            // 先读取并忽略第一行
            std::getline(blockStream, line);
            // 然后读取剩下的内容
            while (std::getline(blockStream, line)) {
                // 确保读取的行不是最后一行
                if (line != "))") {
                    Face_tri face;
                    std::string hexNode1, hexNode2, hexNode3, hexCell1, hexCell2;
                    std::istringstream lineStream(line);
                    lineStream >> hexNode1 >> hexNode2 >> hexNode3 >> hexCell1 >> hexCell2;
                    // 将十六进制字符串转换为整数
                    face.pointid[0] = std::stoi(hexNode1, nullptr, 16);
                    face.pointid[1] = std::stoi(hexNode2, nullptr, 16);
                    face.pointid[2] = std::stoi(hexNode3, nullptr, 16);
                    face.cellid[0] = std::stoi(hexCell1, nullptr, 16);
                    face.cellid[1] = std::stoi(hexCell2, nullptr, 16);
                    face.id = casdata.faces.size() + 1;
                    casdata.faces.emplace_back(face);
                }
            }
        }
    }
    return casdata;
    }
neuData readNeu(std::ifstream& neufile) {
    neuData neudata;
    std::string line;
    for (int i = 0; i < 6; ++i) {
        std::getline(neufile, line);
    }
    int Numnp, Nelem, NGrps, Nbsets, NDCFD, Ndfvl;
    neufile >> Numnp >> Nelem >> NGrps >> Nbsets >> NDCFD >> Ndfvl; std::getline(neufile, line);
    neudata.dim = NDCFD;
    neudata.num_cells = Nelem;
    neudata.num_points = Numnp;
    std::getline(neufile, line);
    std::getline(neufile, line);
    for (int i = 0; i < Numnp; ++i) {
        int id;
        double x, y, z;
        neufile >> id >> x >> y >> z; std::getline(neufile, line);
        neudata.points.emplace_back(id, x, y, z);
    }
    std::getline(neufile, line);
    std::getline(neufile, line);
    Cell_Tet cell;
    for (int i = 0; i < Nelem; ++i) {
        int ilabel = 1;
        int id, type, NDP, n1, n2, n3, n4;
        neufile >> id >> type >> NDP >> n1 >> n2 >> n3 >> n4; std::getline(neufile, line);
        if (type == 6) {
            cell.id = id;
            cell.Typeid = ilabel;
            cell.pointid[0] = n1;
            cell.pointid[1] = n2;
            cell.pointid[2] = n3;
            cell.pointid[3] = n4;
            neudata.cells.emplace_back(cell);
        }
    }
    std::getline(neufile, line);
    while (std::getline(neufile, line)) {
        if (line.substr(0, 12) == "ENDOFSECTION") {
            break;
        }
    }
    for (int i = 0; i < Nbsets; ++i) {
        // 读取边界信息
        std::getline(neufile, line);
        std::string bsetName;
        Region reg;
        int type, Ncell, Value, Ibcode;
        neufile >> bsetName >> type >> Ncell >> Value >> Ibcode; std::getline(neufile, line);
        int id = bsetName[bsetName.length() - 1] - '0';
        reg.rid = id;
        reg.Ncell = Ncell;
        for (int j = 0; j < Ncell; ++j) {
            int cellid, celltype, face2cellid;
            neufile >> cellid >> celltype >> face2cellid; std::getline(neufile, line);
            reg.cellid.push_back(cellid);
            reg.celltype.push_back(celltype);
            reg.face2cellid.push_back(face2cellid);   
        }
        neudata.regions.emplace_back(reg);
        std::getline(neufile, line);
    }
    neufile.close();
    return neudata;
}

mshData readMsh(std::ifstream& mshfile)
{
    return mshData();
}
