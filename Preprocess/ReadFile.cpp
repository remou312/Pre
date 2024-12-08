#include "ReadFile.h"
/*
Data ReadCase(std::ifstream& casfile) {
    Data data;
    std::string line;
    int& dimension = data.dim;
    int& NNode = data.num_points;
    int& NFace = data.num_faces;
    int& NCell = data.num_cells;
    std::vector<Point_3d>& nodes = data.points;
    int node_id = 0;
    // 定义维度正则表达式
    std::regex read_dimension(R"(\(2\s+(\d+)\))");
    // 定义节点数正则表达式
    std::regex read_nnode(R"(\(10\s+\(0\s+1\s+([0-9A-Fa-f]+)\s+\d+\s+\d+\)\))");
    //定义面数正则表达式
    std::regex read_nface(R"(\(13\s*\(0\s+1\s+([0-9A-Fa-f]+)\s+\d+\)\))");
    //定义单元数正则表达式
    std::regex read_ncell(R"(\(12\s*\(0\s+1\s+([0-9A-Fa-f]+)\s+\d+\)\))");
    //定义节点模块正则表达式
    std::regex nodeStartRegex(R"(\(10 \(.*\)\()");// 匹配以"(10 ("开头，后面跟着任意字符，再以"("结尾的字符串
    bool found_dimension = false;
    bool found_nnode = false;
    bool found_nface = false;
    bool found_ncell = false;
    bool parsingNodes = false;
    std::smatch match;
    //循环读取文件，获取维度，节点数，面数，单元数等信息
    while (std::getline(casfile, line)) {
        if (std::regex_search(line, match, read_dimension)) {
            dimension = std::stoi(match[1]);
            found_dimension = true;
        }
        if (std::regex_search(line, match, read_nnode)) {
            NNode = std::stoi(match[1], nullptr, 16);
            found_nnode = true;
        }
        if (std::regex_search(line, match, read_nface)) {
            NFace = std::stoi(match[1], nullptr, 16);
            found_nface = true;
        }
        if (std::regex_search(line, match, read_ncell)) {
            NCell = std::stoi(match[1], nullptr, 16);
            found_ncell = true;
        }
        if (found_dimension && found_nnode && found_nface && found_ncell) {
            break;
        }
    }
    {
        std::cout << "Dimension: " << data.dim << std::endl;
        std::cout << "NNode: " << data.num_points << std::endl;
        std::cout << "NFace: " << data.num_faces << std::endl;
        std::cout << "NCell: " << data.num_cells << std::endl;
    }
    //循环读取文件，获取节点坐标信息
    while (std::getline(casfile, line)) {
        // 检查当前行是否是节点数据块的开始
        if (std::regex_search(line, match, nodeStartRegex)) {
            parsingNodes = true;
            continue; // 跳过这一行，因为它只是节点数据块的开始
        }
        // 如果正在解析节点，并且遇到数据块的结束，则停止
        if (parsingNodes&&line == "))") {
            parsingNodes = false;
            break;
        }
        if (parsingNodes) {
            std::istringstream lineStream(line);
            double x, y, z;
            lineStream >> x >> y >> z;
            node_id++;
            nodes.emplace_back(node_id,x, y, z);
        }
    }
    {
        std::cout <<"Total " << nodes.size() << " nodes have been read" << std::endl;
    }
    //循环读取文件，获取面信息
    while (std::getline(casfile, line)) 
    {
        // 跳过
    }
    casfile.close();
    return data;
}
*/
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
                    double x, y, z;
                    std::istringstream lineStream(line);
                    lineStream >> x >> y >> z;
                    casdata.points.emplace_back(casdata.points.size() + 1, x, y, z);

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
                    std::string hexNode1, hexNode2, hexNode3, hexCell1, hexCell2;
                    std::istringstream lineStream(line);
                    lineStream >> hexNode1 >> hexNode2 >> hexNode3 >> hexCell1 >> hexCell2;
                    // 将十六进制字符串转换为整数
                    int node1 = std::stoi(hexNode1, nullptr, 16);
                    int node2 = std::stoi(hexNode2, nullptr, 16);
                    int node3 = std::stoi(hexNode3, nullptr, 16);
                    int cell1 = std::stoi(hexCell1, nullptr, 16);
                    int cell2 = std::stoi(hexCell2, nullptr, 16);
                    casdata.faces.emplace_back(casdata.faces.size() + 1, node1, node2, node3, cell1, cell2);
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
    for (int i = 0; i < Nelem; ++i) {
        Cell_Tet cell;
        int id, type, NDP, n1, n2, n3, n4;
        neufile >> id >> type >> NDP >> n1 >> n2 >> n3 >> n4; std::getline(neufile, line);
        cell.id = id;
        cell.Typeid = type;
        cell.pointid1 = n1;
        cell.pointid2 = n2;
        cell.pointid3 = n3;
        cell.pointid4 = n4;
        neudata.cells.emplace_back(cell);
    }
    std::getline(neufile, line);
    while (std::getline(neufile, line)) {
        //打印每一行内容
        if (line.substr(0, 12) == "ENDOFSECTION") {
            break;
        }
    }
    for (int i = 0; i < Nbsets; ++i) {
        // 读取边界信息
        std::getline(neufile, line);
        std::string bsetName;
        bnd bnd;
        int type, Ncell, Value, Ibcode;
        neufile >> bsetName >> type >> Ncell >> Value >> Ibcode; std::getline(neufile, line);
        int id = bsetName[bsetName.length() - 1] - '0';
        bnd.id = id;
        bnd.Ncell = Ncell;
        for (int j = 0; j < Ncell; ++j) {
            int cellid, celltype, face2cellid;
            neufile >> cellid >> celltype >> face2cellid; std::getline(neufile, line);
            bnd.cellid.push_back(cellid);
            bnd.celltype.push_back(celltype);
            bnd.face2cellid.push_back(face2cellid);
            neudata.bnds.emplace_back(bnd);
        }
        std::getline(neufile, line);
    }
    neufile.close();
    return neudata;
}