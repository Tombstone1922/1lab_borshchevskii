#include "MethodHandler.h"
#include "../Core/NumberGenerator.h"
#include "../Processors/MultiplierProcessor.h"
#include "../Processors/FibonacciProcessor.h"
#include "../Processors/PowerProcessor.h"
#include "../Processors/FactorialProcessor.h"
#include "../Utils/utils.h"
#include "../Core/TablePrinter.h"
#include "../Core/DataHandler.h"

void MethodHandler::runMultiplication(const std::vector<long long>& N_values, const std::vector<int>& M_values) {
    MultiplierProcessor mulProcessor(85);
    std::map<long long, std::map<int, double>> timesMul;
    TablePrinter printer;

    for (long long N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        NumberGenerator::generateFile(inputFile, N);

        for (int M : M_values) {
            DataHandler handler;
            handler.loadFromFile(inputFile);

            double timeSec = measureTime([&]() {
                if (M == 1) handler.processSequential(mulProcessor);
                else handler.processParallel(mulProcessor, M);
                }) / 1'000'000.0;

            timesMul[N][M] = timeSec;
        }
    }
    printer.printTableVertical(timesMul, "Multiplication", N_values, M_values);
}

void MethodHandler::runFibonacci(const std::vector<long long>& N_values, const std::vector<int>& M_values) {
    FibonacciProcessor fibProcessor;
    std::map<long long, std::map<int, double>> timesFib;
    TablePrinter printer;

    for (long long N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        NumberGenerator::generateFile(inputFile, N);

        for (int M : M_values) {
            DataHandler handler;
            handler.loadFromFile(inputFile);

            double timeSec = measureTime([&]() {
                if (M == 1) handler.processSequential(fibProcessor);
                else handler.processParallel(fibProcessor, M);
                }) / 1'000'000.0;

            timesFib[N][M] = timeSec;
        }
    }
    printer.printTableVertical(timesFib, "Fibonacci", N_values, M_values);
}

void MethodHandler::runPower(const std::vector<long long>& N_values, const std::vector<int>& M_values) {
    PowerProcessor powerProcessor;
    std::map<long long, std::map<int, double>> timesPower;
    TablePrinter printer;

    for (long long N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        NumberGenerator::generateFile(inputFile, N);

        for (int M : M_values) {
            DataHandler handler;
            handler.loadFromFile(inputFile);

            double timeSec = measureTime([&]() {
                if (M == 1) handler.processSequential(powerProcessor);
                else handler.processParallel(powerProcessor, M);
                }) / 1'000'000.0;

            timesPower[N][M] = timeSec;
        }
    }
    printer.printTableVertical(timesPower, "Power", N_values, M_values);
}

void MethodHandler::runFactorial(const std::vector<long long>& N_values, const std::vector<int>& M_values) {
    FactorialProcessor factProcessor;
    std::map<long long, std::map<int, double>> timesFact;
    TablePrinter printer;

    for (long long N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        NumberGenerator::generateFile(inputFile, N);

        for (int M : M_values) {
            DataHandler handler;
            handler.loadFromFile(inputFile);

            double timeSec = measureTime([&]() {
                if (M == 1) handler.processSequential(factProcessor);
                else handler.processParallel(factProcessor, M);
                }) / 1'000'000.0;

            timesFact[N][M] = timeSec;
        }
    }
    printer.printTableVertical(timesFact, "Factorial", N_values, M_values);
}

void MethodHandler::runUnevenSplit(const std::vector<long long>& N_values, const std::vector<int>& M_values) {
    MultiplierProcessor mulProcessor(85);
    std::map<long long, std::map<int, double>> timesUneven;
    TablePrinter printer;

    for (long long N : N_values) {
        std::string inputFile = "data_" + std::to_string(N) + ".txt";
        NumberGenerator::generateFile(inputFile, N);

        for (int M : M_values) {
            std::vector<size_t> splits(M, N / M);
            splits[0] = N / 10;  // Ïåðâûé ïîòîê ïîëó÷àåò 10%
            splits[1] = N - splits[0];  // Âòîðîé ïîòîê ïîëó÷àåò îñòàâøååñÿ

            DataHandler handler;
            handler.loadFromFile(inputFile);

            double timeSec = measureTime([&]() {
                handler.processUneven(mulProcessor, splits);
                }) / 1'000'000.0;

            timesUneven[N][M] = timeSec;
        }
    }
    printer.printTableVertical(timesUneven, "Uneven Split (Multiplication)", N_values, M_values);
}
