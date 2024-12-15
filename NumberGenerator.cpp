#include "NumberGenerator.h"
#include <fstream>
#include <stdexcept>

void NumberGenerator::generateFile(const std::string& filename, int N) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    for (int i = 1; i <= N; ++i) {
        fout << i << "\n";
    }
    fout.close();
}
