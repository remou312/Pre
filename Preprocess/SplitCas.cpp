#include "SplitCas.h"

std::vector<std::string> splitCas(std::ifstream& casfile) {
    std::vector<std::string> blocks;
    std::string currentBlock;
    int balance = 0;

    char ch;
    while (casfile.get(ch)) {  // �������������ַ���ȡ
        currentBlock += ch; // ��ӵ�ǰ�ַ�����ǰ��

        if (ch == '(') {
            balance++; // ���Ӳ㼶
        }
        else if (ch == ')') {
            balance--; // ���ٲ㼶
        }

        // �����ǹر�һ��Բ����ʱ�����ƽ��״̬
        if (balance == 0) {
            // ��鵱ǰ���Ƿ�ֻ�����ո�
            if (!currentBlock.empty() && currentBlock.find_first_not_of(" \n\t") != std::string::npos && currentBlock.find("(0") != 0) {
                blocks.push_back(currentBlock); // �洢��ǰ��
            }
            currentBlock.clear(); // ��յ�ǰ���Թ��´�ʹ��
        }
    }
    casfile.close(); // �ر�������
    return blocks;
}