#include "FactorialProcessor.h"

FactorialProcessor::FactorialProcessor() {
   
}


int FactorialProcessor::processElement(int element) const {
    if (element < 0) return 0; 
    int result = 1;
    for (int i = 2; i <= element; ++i) {
        result *= i; 
    }
    return result;
}
