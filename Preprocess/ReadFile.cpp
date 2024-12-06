#include "ReadFile.h"
Data ReadCase(std::ifstream& casfile) {
    Data data;
    std::string line;
    int dimension = 0;
    // Read Dimension
    std::regex read_dimension(R"(\(2\s+(\d+)\))");
    std::smatch match;
    if (std::getline(casfile, line)) {
        if (std::regex_search(line, match, read_dimension)) {
            dimension = std::stoi(match[1]);
        }
    }
    std::cout << "Dimension: " << dimension << std::endl;






    casfile.close();
    return data;
}