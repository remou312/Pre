#include "SplitCas.h"

std::vector<std::string> splitCas(std::ifstream& casfile) {
    std::vector<std::string> blocks;
    std::string currentBlock;
    int balance = 0;

    char ch;
    while (casfile.get(ch)) {  // 从输入流中逐字符读取
        currentBlock += ch; // 添加当前字符到当前块

        if (ch == '(') {
            balance++; // 增加层级
        }
        else if (ch == ')') {
            balance--; // 减少层级
        }

        // 当我们关闭一个圆括号时，检查平衡状态
        if (balance == 0) {
            // 检查当前块是否只包含空格
            if (!currentBlock.empty() && currentBlock.find_first_not_of(" \n\t") != std::string::npos && currentBlock.find("(0") != 0) {
                blocks.push_back(currentBlock); // 存储当前块
            }
            currentBlock.clear(); // 清空当前块以供下次使用
        }
    }
    casfile.close(); // 关闭输入流
    return blocks;
}