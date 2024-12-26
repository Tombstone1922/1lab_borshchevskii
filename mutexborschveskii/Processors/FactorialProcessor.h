#ifndef FACTORIALPROCESSOR_H
#define FACTORIALPROCESSOR_H

#include "IProcessor.h"

class FactorialProcessor : public IProcessor {
public:
    FactorialProcessor(); 
    int processElement(int element) const override; 
};

#endif
