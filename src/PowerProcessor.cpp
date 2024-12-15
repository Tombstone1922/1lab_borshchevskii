#include "PowerProcessor.h"
#include <cmath>

PowerProcessor::PowerProcessor() {
    
}

int PowerProcessor::processElement(int element) const {
    double x = static_cast<double>(element);
    x = std::pow(x, 0.25);
    x = std::pow(x, 1.3);
    x = std::pow(x, 0.75);
    x = std::pow(x, 11.3); 
    x = std::pow(x, 0.55);
    x = std::pow(x, 11.3);
    return static_cast<int>(std::round(x));
}
