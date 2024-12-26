#include "utils.h"
#include <fstream>
#include <stdexcept>

void generateFile(const std::string& filename, int N) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    for (int i = 1; i <= N; ++i) {
        fout << i << "\n";
    }
    fout.close();
}
