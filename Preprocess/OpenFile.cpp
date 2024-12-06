#include "OpenFile.h"
std::ifstream openCasFile() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    // 检查并添加后缀 ".cas"
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".cas") {
        filename += ".cas";
    }
    // 循环直到文件存在并成功打开
    while (true) {
        if (fs::exists(filename)) {
            std::ifstream file(filename);
            if (file.is_open()) {
                std::cout << "File " << filename << " opened successfully." << std::endl;
                return file;
            }
            else {
                std::cerr << "Error: Could not open file " << filename << std::endl;
            }
        }
        else {
            std::cerr << "Error: File " << filename << " does not exist. Please enter a valid filename." << std::endl;
            std::cout << "Enter filename: ";
            std::cin >> filename;

            // 检查并添加后缀 ".cas"
            if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".cas") {
                filename += ".cas";
            }
        }
    }
}
//std::ifstream openMshFile() {}