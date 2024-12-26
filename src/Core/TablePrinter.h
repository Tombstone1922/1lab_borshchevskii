#ifndef TABLEPRINTER_H
#define TABLEPRINTER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

class TablePrinter {
public:
    // Èñïðàâëåííûé ìåòîä äëÿ ïîääåðæêè long long â êëþ÷àõ
    void printTableVertical(
        const std::map<long long, std::map<int, double>>& results,
        const std::string& title,
        const std::vector<long long>& N_values,
        const std::vector<int>& M_values
    ) const {
        std::cout << "\n===== " << title << " =====\n";
        std::cout << std::left
            << std::setw(20) << "N (Number of Elements)"
            << std::setw(20) << "M (Number of Threads)"
            << std::setw(20) << "Execution Time [ns]\n";

        for (auto N : N_values) {
            for (auto M : M_values) {
                // Ïðîâåðÿåì íàëè÷èå çíà÷åíèé ïåðåä äîñòóïîì
                if (results.find(N) != results.end() && results.at(N).find(M) != results.at(N).end()) {
                    long long timeNs = static_cast<long long>(results.at(N).at(M) * 1'000'000'000);
                    std::cout << std::left
                        << std::setw(20) << N
                        << std::setw(20) << M
                        << std::setw(20) << timeNs << "\n";
                }
            }
        }
    }
};

#endif
