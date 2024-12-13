#ifndef POWERPROCESSOR_H
#define POWERPROCESSOR_H

#include "IProcessor.h"

class PowerProcessor : public IProcessor {
    int power;
public:
    PowerProcessor(int p);
    int processElement(int element) const override;
};

#endif
