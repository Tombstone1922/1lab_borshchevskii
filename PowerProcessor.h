#ifndef POWERPROCESSOR_H
#define POWERPROCESSOR_H

#include "IProcessor.h"

class PowerProcessor : public IProcessor {
public:
    PowerProcessor(); // конструктор по умолчанию
    int processElement(int element) const override;
};

#endif
