#include "DataHandler.h"
#include <fstream>
#include <thread>
#include <numeric>
#include <stdexcept>

void DataHandler::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("Cannot open file");
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
        throw std::runtime_error("Cannot open file for writing");
    }
    for (auto& d : data) {
        fout << d << "\n";
    }
    fout.close();
}

void DataHandler::setData(std::vector<int>&& newData) {
    data = std::move(newData);
}

const std::vector<int>& DataHandler::getData() const {
    return data;
}

void DataHandler::processSequential(const IProcessor& processor) {
    for (auto& elem : data) {
        elem = processor.processElement(elem);
    }
}

void DataHandler::processParallel(const IProcessor& processor, int threadCount) {
    if (threadCount <= 0) threadCount = 1;
    std::vector<std::thread> threads;
    int dataSize = static_cast<int>(data.size());
    int chunkSize = dataSize / threadCount;
    int remainder = dataSize % threadCount;

    int start = 0;
    for (int i = 0; i < threadCount; ++i) {
        int currentChunkSize = chunkSize + (i < remainder ? 1 : 0);
        int end = start + currentChunkSize;
        // Захватим всё по ссылке, кроме start и end, которые передаём по значению
        threads.emplace_back([&, start, end]() {
            for (int idx = start; idx < end; ++idx) {
                data[idx] = processor.processElement(data[idx]);
            }
            });
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }
}

void DataHandler::processParallelCustom(const IProcessor& processor, const std::vector<int>& partitionSizes) {
    int sum = std::accumulate(partitionSizes.begin(), partitionSizes.end(), 0);
    if (sum != (int)data.size()) {
        throw std::runtime_error("Partition sizes do not sum up to data size");
    }

    std::vector<std::thread> threads;
    int start = 0;
    for (auto size : partitionSizes) {
        int end = start + size;
        threads.emplace_back([&, start, end]() {
            for (int idx = start; idx < end; ++idx) {
                data[idx] = processor.processElement(data[idx]);
            }
            });
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }
}
