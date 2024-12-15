#ifndef MULTIPLIERPROCESSOR_H
#define MULTIPLIERPROCESSOR_H

#include "IProcessor.h"

class MultiplierProcessor : public IProcessor {
    int factor;
public:
    MultiplierProcessor(int f);
    int processElement(int element) const override;
};

#endif
