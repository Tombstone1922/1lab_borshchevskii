#include "DataHandler.h"
#include <fstream>
#include <thread>
#include <numeric>
#include <stdexcept>

void DataHandler::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    data.clear();
    int val;
    while (fin >> val) {
        data.push_back(val);
    }
    fin.close();
}

void DataHandler::saveToFile(const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    for (auto& d : data) {
        fout << d << "\n";
    }
    fout.close();
}

void DataHandler::processSequential(const IProcessor& processor) {
    for (auto& elem : data) {
        elem = processor.processElement(elem);
    }
}

void DataHandler::processParallel(const IProcessor& processor, int threadCount) {
    if (threadCount <= 0) threadCount = 1;
    std::vector<std::thread> threads;
    size_t dataSize = data.size();
    size_t chunkSize = dataSize / threadCount;
    size_t remainder = dataSize % threadCount;

    size_t start = 0;
    for (int i = 0; i < threadCount; ++i) {
        size_t currentChunkSize = chunkSize + (i < remainder ? 1 : 0);
        size_t end = start + currentChunkSize;
        threads.emplace_back([&, start, end]() {
            for (size_t idx = start; idx < end; ++idx) {
                data[idx] = processor.processElement(data[idx]);
            }
            });
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }
}

void DataHandler::processUneven(const IProcessor& processor, const std::vector<size_t>& splits) {
    size_t totalSize = std::accumulate(splits.begin(), splits.end(), 0);
    if (totalSize != data.size()) {
        throw std::runtime_error("Split sizes do not sum up to data size");
    }

    std::vector<std::thread> threads;
    size_t start = 0;

    for (size_t size : splits) {
        size_t end = start + size;
        threads.emplace_back([&, start, end]() {
            for (size_t idx = start; idx < end; ++idx) {
                data[idx] = processor.processElement(data[idx]);
            }
            });
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }
}

const std::vector<int>& DataHandler::getData() const {
    return data;
}

void DataHandler::setData(std::vector<int>&& newData) {
    data = std::move(newData);
}
