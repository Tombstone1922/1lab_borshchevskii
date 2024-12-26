#ifndef METHODHANDLER_H
#define METHODHANDLER_H

#include <vector>
#include <map>
#include "../Core/DataHandler.h"
#include "../Core/TablePrinter.h"

class MethodHandler {
public:
    static void runMultiplication(const std::vector<long long>& N_values, const std::vector<int>& M_values);
    static void runFibonacci(const std::vector<long long>& N_values, const std::vector<int>& M_values);
    static void runPower(const std::vector<long long>& N_values, const std::vector<int>& M_values);
    static void runFactorial(const std::vector<long long>& N_values, const std::vector<int>& M_values);
    static void runUnevenSplit(const std::vector<long long>& N_values, const std::vector<int>& M_values);
};

#endif // METHODHANDLER_H
