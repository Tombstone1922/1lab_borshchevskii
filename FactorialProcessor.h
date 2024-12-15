#ifndef FACTORIALPROCESSOR_H
#define FACTORIALPROCESSOR_H

#include "IProcessor.h"

class FactorialProcessor : public IProcessor {
public:
    FactorialProcessor(); // Конструктор
    int processElement(int element) const override; // Метод для вычисления факториала
};

#endif
