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

//使用栈结构将文件进行分块处理
Data ReadCase(std::ifstream& casfile) {
    std::vector<std::string> blocks = SplitCas(casfile);
    Data data;
    //从blocks中解析信息



















    return data;
    }
