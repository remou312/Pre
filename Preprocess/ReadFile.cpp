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
Data readCase(std::ifstream& casfile) {
    std::vector<std::string> blocks = splitCas(casfile);
    Data data;
    //��blocks�н�����Ϣ
    for (int i = 0; i < blocks.size(); i++)
    {
        //���ά��
        if (blocks[i].substr(0, 2) == "(2") {
            data.dim = blocks[i][3] - '0';
            cout << "Dimension: " << data.dim << endl;
        }
        //���ڵ���
        if (blocks[i].substr(0, 9) == "(10 (0 1 ") {
            std::string subStr = blocks[i].substr(9); // �ӵ�10���ַ���ʼ��ȡʣ�µ��ַ���
            size_t pos = subStr.find(' '); // ���ҵ�һ���ո��λ��

            if (pos != std::string::npos) {
                subStr = subStr.substr(0, pos); // ��ȡ�ӿ�ʼ����һ���ո�����ַ���
            }
            cout << "NNode: " << subStr << endl;
            data.num_points = stoi(subStr, nullptr, 16);
            cout << "NNode: " << data.num_points << endl;
        }
        //�������
        if (blocks[i].substr(0, 9) == "(13 (0 1 ") {
            std::string subStr = blocks[i].substr(9);
            size_t pos = subStr.find(' '); // ���ҵ�һ���ո��λ��

            if (pos != std::string::npos) {
                subStr = subStr.substr(0, pos); // ��ȡ�ӿ�ʼ����һ���ո�����ַ���
            }
            cout << "NFace: " << subStr << endl;
            data.num_faces = stoi(subStr, nullptr, 16);
            cout << "NFace: " << data.num_faces << endl;
        }
        //��ⵥԪ��
        if (blocks[i].substr(0, 9) == "(12 (0 1 ") {
            std::string subStr = blocks[i].substr(9);
            size_t pos = subStr.find(' '); // ���ҵ�һ���ո��λ��

            if (pos != std::string::npos) {
                subStr = subStr.substr(0, pos); // ��ȡ�ӿ�ʼ����һ���ո�����ַ���
            }
            cout << "NCell: " << subStr << endl;
            data.num_cells = stoi(subStr, nullptr, 16);
            cout << "NCell: " << data.num_cells << endl;
        }
        //��ȡ�ڵ�����
        if (blocks[i].substr(0, 5) == "(10 (" && blocks[i].substr(5, 1) != "0") {
            // ���� blocks[i] Ϊ�������ݿ飬���԰��зָ�
            std::istringstream blockStream(blocks[i]);
            std::string line;
            // �ȶ�ȡ�����Ե�һ��
            std::getline(blockStream, line);
            // Ȼ���ȡʣ�µ�����
            while (std::getline(blockStream, line)) {
                // ȷ����ȡ���в������һ��
                if (line != "))") {
                    double x, y, z;
                    std::istringstream lineStream(line);
                    lineStream >> x >> y >> z;
                    data.points.emplace_back(data.points.size() + 1, x, y, z);
                }
            }
        }
        //��ȡ����Ϣ
        if (blocks[i].substr(0, 5) == "(13 (" && blocks[i].substr(5, 1) != "0") {
            // ���� blocks[i] Ϊ�������ݿ飬���԰��зָ�
            std::istringstream blockStream(blocks[i]);
            std::string line;
            // �ȶ�ȡ�����Ե�һ��
            std::getline(blockStream, line);
            // Ȼ���ȡʣ�µ�����
            while (std::getline(blockStream, line)) {
                // ȷ����ȡ���в������һ��
                if (line != "))") {
                    std::string hexNode1, hexNode2, hexNode3, hexCell1, hexCell2;
                    std::istringstream lineStream(line);
                    lineStream >> hexNode1 >> hexNode2 >> hexNode3 >> hexCell1 >> hexCell2;

                    // ��ʮ�������ַ���ת��Ϊ����
                    int node1 = std::stoi(hexNode1, nullptr, 16);
                    int node2 = std::stoi(hexNode2, nullptr, 16);
                    int node3 = std::stoi(hexNode3, nullptr, 16);
                    int cell1 = std::stoi(hexCell1, nullptr, 16);
                    int cell2 = std::stoi(hexCell2, nullptr, 16);
                    data.faces.emplace_back(data.faces.size() + 1, node1, node2, node3, cell1, cell2);
                }
            }
        }

    }

    return data;
    }
