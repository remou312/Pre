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






    // 关闭文件
    ofs.close();
}