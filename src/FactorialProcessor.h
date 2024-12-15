#ifndef FACTORIALPROCESSOR_H
#define FACTORIALPROCESSOR_H

#include "IProcessor.h"

class FactorialProcessor : public IProcessor {
public:
    FactorialProcessor(); // Êîíñòðóêòîð
    int processElement(int element) const override; // Ìåòîä äëÿ âû÷èñëåíèÿ ôàêòîðèàëà
};

#endif
