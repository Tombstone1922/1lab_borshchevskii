#include <iostream>
#include <vector>
#include <map>
#include "MethodHandler.h"

int main() {
    std::vector<long long> N_values;
    std::vector<int> M_values;

    int N_count, M_count;
    std::cout << "Enter the number of N values: ";
    std::cin >> N_count;
    std::cout << "Enter " << N_count << " values for N: ";
    for (int i = 0; i < N_count; ++i) {
        long long N;
        std::cin >> N;
        N_values.push_back(N);
    }

    std::cout << "Enter the number of M values: ";
    std::cin >> M_count;
    std::cout << "Enter " << M_count << " values for M: ";
    for (int i = 0; i < M_count; ++i) {
        int M;
        std::cin >> M;
        M_values.push_back(M);
    }

    int choice;
    std::cout << "Select the method:\n";
    std::cout << "1. Multiplication\n2. Fibonacci\n3. Power\n4. Factorial\n5. Uneven Split\n";
    std::cout << "Enter your choice (1-5): ";
    std::cin >> choice;

    switch (choice) {
    case 1: MethodHandler::runMultiplication(N_values, M_values); break;
    case 2: MethodHandler::runFibonacci(N_values, M_values); break;
    case 3: MethodHandler::runPower(N_values, M_values); break;
    case 4: MethodHandler::runFactorial(N_values, M_values); break;
    case 5: MethodHandler::runUnevenSplit(N_values, M_values); break;
    default: std::cout << "Invalid choice.\n"; break;
    }

    return 0;
}
