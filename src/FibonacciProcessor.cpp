#include "FibonacciProcessor.h"

int FibonacciProcessor::processElement(int element) const {
    return fib_iterative_mod(element);
}

int FibonacciProcessor::fib_iterative_mod(int n) const {
    const int MOD = 1000000; 
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int temp = (a + b) % MOD;
        a = b;
        b = temp;
    }
    return b;
}
