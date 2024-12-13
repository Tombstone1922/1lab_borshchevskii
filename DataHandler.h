#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <vector>
#include <string>
#include "IProcessor.h"

class DataHandler {
private:
    std::vector<int> data;
public:
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void setData(std::vector<int>&& newData);
    const std::vector<int>& getData() const;

    // Обработка
    void processSequential(const IProcessor& processor);
    void processParallel(const IProcessor& processor, int threadCount);
    void processParallelCustom(const IProcessor& processor, const std::vector<int>& partitionSizes);
};

#endif
