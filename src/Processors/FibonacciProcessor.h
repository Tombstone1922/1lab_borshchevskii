#ifndef FIBONACCIPROCESSOR_H
#define FIBONACCIPROCESSOR_H

#include "IProcessor.h"

class FibonacciProcessor : public IProcessor {
public:
    int processElement(int element) const override;
private:
    int fib_iterative_mod(int n) const;
};

#endif
