#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <string>

class NumberGenerator {
public:
    // ���������� ���� filename � ������� �� 1 �� N
    static void generateFile(const std::string& filename, int N);
};

#endif
