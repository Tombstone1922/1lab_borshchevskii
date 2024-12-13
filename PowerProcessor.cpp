#include "PowerProcessor.h"
#include <cmath>

PowerProcessor::PowerProcessor(int p) : power(p) {}

int PowerProcessor::processElement(int element) const {
    return static_cast<int>(std::pow(element, power));
}
