#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <string>

class NumberGenerator {
public:
    // Ãåíåðèðóåò ôàéë filename ñ ÷èñëàìè îò 1 äî N
    static void generateFile(const std::string& filename, int N);
};

#endif
