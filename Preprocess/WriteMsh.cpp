#include "WriteMsh.h"

void WriteMsh(const geoData& data)
{
    std::string filename;
    std::cout << "Please enter a file name:";
    std::cin >> filename;
    while (true) {
        if (!filename.empty()) {  // ��������Ƿ�Ϊ��
            break;  // ������Ч���˳�ѭ��
        }
        else {
            std::cout << "Invalid input. Please enter the file name again:";
        }
    }
    // ����Ƿ������չ������û������� ".msh"
    if (filename.find_last_of(".") == std::string::npos) {
        filename += ".msh";
    }
    else {
        std::string extension = filename.substr(filename.find_last_of("."));
        if (extension != ".msh") {
            filename = filename.substr(0, filename.find_last_of(".")) + ".msh";
        }
    }
    // ���ļ�
    std::ofstream ofs(filename, std::ios::out);
    // ��ȡgeoData����д��.msh�ļ�






    // �ر��ļ�
    ofs.close();
}