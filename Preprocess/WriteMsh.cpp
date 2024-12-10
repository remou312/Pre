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
    // д���ļ�ͷ����Ϣ
    ofs << "version 1.0" << "\n";
    ofs << "Scale: " << data.scale << "\n";
    // д�뵥Ԫ��Ϣ
    ofs << "ce:cells" << "\n";
    ofs <<"\t"<< data.num_cells << "\n";
    for (int i = 0; i < data.num_cells; i++) {
        ofs << "\t" << i+1 << "\t" << data.cells[i].Typeid<< "\t" 
            << data.cells[i].centroid[0]<<"\t" << data.cells[i].centroid[1]<<
            "\t" << data.cells[i].centroid[2]<<"\t"
            <<data.cells[i].volume<< "\n";
        }
    // д�뵥Ԫ����Ϣ
    ofs<<"cf:cell faces"<<"\n";
    ofs<<"\t"<<"4" << "\n";
    for (int i = 0; i < data.num_cells; i++) {
        ofs << "\t" << i+1 << "\t" << "4"<< "\t" 
            << data.cells[i].faceid1<< "\t" << data.cells[i].faceid2<< "\t" 
            << data.cells[i].faceid3<< "\t" << data.cells[i].faceid4<< "\t";
    }
    //// д������Ϣ
    //ofs<<"fc:faces"<<"\n";
    //ofs<<"\t"<<data.num_faces<<"\n";
    //for (int i = 0; i < data.num_faces; i++) {

    //}
    // �ر��ļ�
    ofs.close();
}