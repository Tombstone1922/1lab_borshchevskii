#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono> // äëÿ std::chrono

void generateFile(const std::string& filename, int N);

template<typename Func>
long long measureTime(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

#endif
