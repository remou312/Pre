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
    // ����ά��������ʽ
    std::regex read_dimension(R"(\(2\s+(\d+)\))");
    // ����ڵ���������ʽ
    std::regex read_nnode(R"(\(10\s+\(0\s+1\s+([0-9A-Fa-f]+)\s+\d+\s+\d+\)\))");
    //��������������ʽ
    std::regex read_nface(R"(\(13\s*\(0\s+1\s+([0-9A-Fa-f]+)\s+\d+\)\))");
    //���嵥Ԫ��������ʽ
    std::regex read_ncell(R"(\(12\s*\(0\s+1\s+([0-9A-Fa-f]+)\s+\d+\)\))");
    //����ڵ�ģ��������ʽ
    std::regex nodeStartRegex(R"(\(10 \(.*\)\()");// ƥ����"(10 ("��ͷ��������������ַ�������"("��β���ַ���
    bool found_dimension = false;
    bool found_nnode = false;
    bool found_nface = false;
    bool found_ncell = false;
    bool parsingNodes = false;
    std::smatch match;
    //ѭ����ȡ�ļ�����ȡά�ȣ��ڵ�������������Ԫ������Ϣ
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
    //ѭ����ȡ�ļ�����ȡ�ڵ�������Ϣ
    while (std::getline(casfile, line)) {
        // ��鵱ǰ���Ƿ��ǽڵ����ݿ�Ŀ�ʼ
        if (std::regex_search(line, match, nodeStartRegex)) {
            parsingNodes = true;
            continue; // ������һ�У���Ϊ��ֻ�ǽڵ����ݿ�Ŀ�ʼ
        }
        // ������ڽ����ڵ㣬�����������ݿ�Ľ�������ֹͣ
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
    //ѭ����ȡ�ļ�����ȡ����Ϣ
    while (std::getline(casfile, line)) 
    {
        // ����
    }
    casfile.close();
    return data;
}
*/

//ʹ��ջ�ṹ���ļ����зֿ鴦��
Data ReadCase(std::ifstream& casfile) {
    std::vector<std::string> blocks = SplitCas(casfile);
    Data data;
    //��blocks�н�����Ϣ



















    return data;
    }
