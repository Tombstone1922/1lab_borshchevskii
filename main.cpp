#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "DataHandler.h"
#include "MultiplierProcessor.h"
#include "FibonacciProcessor.h"
#include "PowerProcessor.h"
#include "utils.h"

int main() {
    // Наборы данных
    std::vector<int> N_values = { 10, 100, 500, 1000, 5000, 10000, 20000, 30000 };
    std::vector<int> M_values = { 1, 2, 4, 8, 10, 20, 30, 100 };

    // Формат вывода
    std::cout << std::fixed << std::setprecision(6);

    // Структуры для хранения времен
    // Последовательная обработка
    std::map<int, double> timesSequentialMul;
    std::map<int, double> timesSequentialFib;
    std::map<int, double> timesSequentialPow;

    // Параллельная обработка
    std::map<int, std::map<int, double>> timesParallelMul;
    std::map<int, std::map<int, double>> timesParallelFib;
    std::map<int, std::map<int, double>> timesParallelPow;

    MultiplierProcessor mulProcessor(2);
    FibonacciProcessor fibProcessor;
    PowerProcessor powerProcessor(2); // Возводим в квадрат

    const int colWidth = 12;

    // -------------------------------------
    // ПОСЛЕДОВАТЕЛЬНАЯ ОБРАБОТКА
    // -------------------------------------

    // Multiplication (Sequential)
    std::cout << "\n=== Sequential Results (Multiplication, seconds) ===\n";
    std::cout << std::left << std::setw(colWidth) << "N"
        << std::setw(colWidth) << "Time(s)"
        << "\n"
        << std::string(colWidth * 2, '-') << "\n";

    for (int N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        generateFile(inputFile, N);

        DataHandler handler;
        handler.loadFromFile(inputFile);

        long long seqTimeMicro = measureTime([&]() {
            handler.processSequential(mulProcessor);
            });
        double seqTimeSec = seqTimeMicro / 1'000'000.0;
        timesSequentialMul[N] = seqTimeSec;

        std::cout << std::left << std::setw(colWidth) << N
            << std::setw(colWidth) << timesSequentialMul[N] << "\n";
    }

    // Fibonacci (Sequential)
    std::cout << "\n=== Sequential Results (Fibonacci, seconds) ===\n";
    std::cout << std::left << std::setw(colWidth) << "N"
        << std::setw(colWidth) << "Time(s)"
        << "\n"
        << std::string(colWidth * 2, '-') << "\n";

    for (int N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        // Файл уже сгенерирован выше при умножении, можно не генерировать снова

        DataHandler handler;
        handler.loadFromFile(inputFile);

        long long seqTimeMicroFib = measureTime([&]() {
            handler.processSequential(fibProcessor);
            });
        double seqTimeSecFib = seqTimeMicroFib / 1'000'000.0;
        timesSequentialFib[N] = seqTimeSecFib;

        std::cout << std::left << std::setw(colWidth) << N
            << std::setw(colWidth) << timesSequentialFib[N] << "\n";
    }

    // Power (Sequential) - возведение в квадрат
    std::cout << "\n=== Sequential Results (Power=2, seconds) ===\n";
    std::cout << std::left << std::setw(colWidth) << "N"
        << std::setw(colWidth) << "Time(s)"
        << "\n"
        << std::string(colWidth * 2, '-') << "\n";

    for (int N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";

        DataHandler handler;
        handler.loadFromFile(inputFile);

        long long seqTimeMicroPow = measureTime([&]() {
            handler.processSequential(powerProcessor);
            });
        double seqTimeSecPow = seqTimeMicroPow / 1'000'000.0;
        timesSequentialPow[N] = seqTimeSecPow;

        std::cout << std::left << std::setw(colWidth) << N
            << std::setw(colWidth) << timesSequentialPow[N] << "\n";
    }

    // -------------------------------------
    // ПАРАЛЛЕЛЬНАЯ ОБРАБОТКА
    // -------------------------------------

    // Multiplication (Parallel)
    std::cout << "\n=== Parallel Results (Multiplication, seconds) ===\n";
    std::cout << std::left << std::setw(colWidth) << "N \\ M";
    for (auto M : M_values) {
        std::cout << std::setw(colWidth) << M;
    }
    std::cout << "\n"
        << std::string(colWidth * (1 + (int)M_values.size()), '-') << "\n";

    for (int N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        DataHandler handler;
        handler.loadFromFile(inputFile);

        std::map<int, double> currentParallelResults;
        for (int M : M_values) {
            if (M == 1) {
                currentParallelResults[M] = timesSequentialMul[N];
            }
            else {
                handler.loadFromFile(inputFile);
                long long parTimeMicro = measureTime([&]() {
                    handler.processParallel(mulProcessor, M);
                    });
                double parTimeSec = parTimeMicro / 1'000'000.0;
                currentParallelResults[M] = parTimeSec;
            }
        }

        timesParallelMul[N] = currentParallelResults;

        std::cout << std::left << std::setw(colWidth) << N;
        for (auto M : M_values) {
            std::cout << std::setw(colWidth) << timesParallelMul[N][M];
        }
        std::cout << "\n";
    }

    // Fibonacci (Parallel)
    std::cout << "\n=== Parallel Results (Fibonacci, seconds) ===\n";
    std::cout << std::left << std::setw(colWidth) << "N \\ M";
    for (auto M : M_values) {
        std::cout << std::setw(colWidth) << M;
    }
    std::cout << "\n"
        << std::string(colWidth * (1 + (int)M_values.size()), '-') << "\n";

    for (int N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        DataHandler handler;
        handler.loadFromFile(inputFile);

        std::map<int, double> currentParallelResultsFib;
        for (int M : M_values) {
            if (M == 1) {
                currentParallelResultsFib[M] = timesSequentialFib[N];
            }
            else {
                handler.loadFromFile(inputFile);
                long long parTimeMicroFib = measureTime([&]() {
                    handler.processParallel(fibProcessor, M);
                    });
                double parTimeSecFib = parTimeMicroFib / 1'000'000.0;
                currentParallelResultsFib[M] = parTimeSecFib;
            }
        }

        timesParallelFib[N] = currentParallelResultsFib;

        std::cout << std::left << std::setw(colWidth) << N;
        for (auto M : M_values) {
            std::cout << std::setw(colWidth) << timesParallelFib[N][M];
        }
        std::cout << "\n";
    }

    // Power (Parallel)
    std::cout << "\n=== Parallel Results (Power=2, seconds) ===\n";
    std::cout << std::left << std::setw(colWidth) << "N \\ M";
    for (auto M : M_values) {
        std::cout << std::setw(colWidth) << M;
    }
    std::cout << "\n"
        << std::string(colWidth * (1 + (int)M_values.size()), '-') << "\n";

    for (int N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        DataHandler handler;
        handler.loadFromFile(inputFile);

        std::map<int, double> currentParallelResultsPow;
        for (int M : M_values) {
            if (M == 1) {
                currentParallelResultsPow[M] = timesSequentialPow[N];
            }
            else {
                handler.loadFromFile(inputFile);
                long long parTimeMicroPow = measureTime([&]() {
                    handler.processParallel(powerProcessor, M);
                    });
                double parTimeSecPow = parTimeMicroPow / 1'000'000.0;
                currentParallelResultsPow[M] = parTimeSecPow;
            }
        }

        timesParallelPow[N] = currentParallelResultsPow;

        std::cout << std::left << std::setw(colWidth) << N;
        for (auto M : M_values) {
            std::cout << std::setw(colWidth) << timesParallelPow[N][M];
        }
        std::cout << "\n";
    }

    std::cout << "\ndone\n";

    return 0;
}
