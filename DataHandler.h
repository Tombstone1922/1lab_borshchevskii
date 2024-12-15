#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "IProcessor.h"
#include <vector>
#include <string>

class DataHandler {
public:
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);

    void processSequential(const IProcessor& processor);
    void processParallel(const IProcessor& processor, int threadCount);
    void processParallelCustom(const IProcessor& processor, const std::vector<int>& partitionSizes);
    void processUneven(const IProcessor& processor, const std::vector<size_t>& splits); // Новый метод

    const std::vector<int>& getData() const;
    void setData(std::vector<int>&& newData);

private:
    std::vector<int> data;
};

#endif // DATAHANDLER_H
