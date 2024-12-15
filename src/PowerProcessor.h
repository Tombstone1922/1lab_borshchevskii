#ifndef POWERPROCESSOR_H
#define POWERPROCESSOR_H

#include "IProcessor.h"

class PowerProcessor : public IProcessor {
public:
    PowerProcessor(); // êîíñòðóêòîð ïî óìîë÷àíèþ
    int processElement(int element) const override;
};

#endif
