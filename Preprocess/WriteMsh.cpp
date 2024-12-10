#include "WriteMsh.h"

void WriteMsh(const geoData& data)
{
    std::string filename;
    std::cout << "Please enter a file name:";
    std::cin >> filename;
    while (true) {
        if (!filename.empty()) {  // 检查输入是否为空
            break;  // 输入有效，退出循环
        }
        else {
            std::cout << "Invalid input. Please enter the file name again:";
        }
    }
    // 检查是否包含扩展名，若没有则加上 ".msh"
    if (filename.find_last_of(".") == std::string::npos) {
        filename += ".msh";
    }
    else {
        std::string extension = filename.substr(filename.find_last_of("."));
        if (extension != ".msh") {
            filename = filename.substr(0, filename.find_last_of(".")) + ".msh";
        }
    }
    // 打开文件
    std::ofstream ofs(filename, std::ios::out);
    // 读取geoData内容写入.msh文件
    // 写入文件头部信息
    ofs << "version 1.0" << "\n";
    ofs << "Scale: " << data.scale << "\n";
    // 写入单元信息
    ofs << "ce:cells" << "\n";
    ofs <<"\t"<< data.num_cells << "\n";
    for (int i = 0; i < data.num_cells; i++) {
        ofs << "\t" << i+1 << "\t" << data.cells[i].Typeid<< "\t" 
            << data.cells[i].centroid[0]<<"\t" << data.cells[i].centroid[1]<<
            "\t" << data.cells[i].centroid[2]<<"\t"
            <<data.cells[i].volume<< "\n";
        }
    // 写入单元面信息
    ofs<<"cf:cell faces"<<"\n";
    ofs<<"\t"<<"4" << "\n";
    for (int i = 0; i < data.num_cells; i++) {
        ofs << "\t" << i+1 << "\t" << "4"<< "\t" 
            << data.cells[i].faceid1<< "\t" << data.cells[i].faceid2<< "\t" 
            << data.cells[i].faceid3<< "\t" << data.cells[i].faceid4<< "\t";
    }
    //// 写入面信息
    //ofs<<"fc:faces"<<"\n";
    //ofs<<"\t"<<data.num_faces<<"\n";
    //for (int i = 0; i < data.num_faces; i++) {

    //}
    // 关闭文件
    ofs.close();
}