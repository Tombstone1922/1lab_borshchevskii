#include "MultiplierProcessor.h"

MultiplierProcessor::MultiplierProcessor(int f) : factor(f) {}

int MultiplierProcessor::processElement(int element) const {
    return element * factor;
}
