#ifndef SYNTACTICAL_ANALYZER_H
#define SYNTACTICAL_ANALYZER_H

#include <string>


class SyntacticalAnalyzer {
    static bool isChar(const char*& str, int deep, char c);
    static bool isDigit(const char*& str, int deep);
    static bool isUnsignedInteger(const char*& str, int deep);
    static bool isInteger(const char*& str, int deep);
    static bool isRealNumber(const char*& str, int deep);

public:
    static bool analyze(const std::string& expression);
};


#endif //SYNTACTICAL_ANALYZER_H
