#ifndef IPROCESSOR_H
#define IPROCESSOR_H

class IProcessor {
public:
    virtual ~IProcessor() = default;
    virtual int processElement(int element) const = 0;
};

#endif
