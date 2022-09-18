#include "SyntacticalAnalyzer.h"
#include "Logger.h"
#include <cctype>

bool SyntacticalAnalyzer::isChar(const char*& str, int deep, char c) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;

    Logger::log("Function isChar('" + std::string(1, *str) + "', '" + c + "') is called [deep=" + std::to_string(deep) + "]\n", DEBUG, deep);

    if (*str == c) {
        str++; // Идем на следующий символ
        result = true;
    }

    // Вывод результата
    if (result) {
        Logger::log("Result: '" + std::string(1, *start) + "' is '" + c + "'\n", DEBUG, deep);
    } else {
        Logger::log("Result: '" + std::string(1, *start) + "' is not '" + c + "'\n", DEBUG, deep);
    }
    
    return result;
}

bool SyntacticalAnalyzer::isDigit(const char*& str, int deep) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;
    
    Logger::log("Function isDigit('" + std::string(1, *str) + "') is called [deep=" + std::to_string(deep) + "]\n", DEBUG, deep);

    if (isdigit(*str)) {
        str++; // Идем на следующий символ
        result = true;
    }

    // Вывод результата
    if (result) {
        Logger::log("Result: '" + std::string(1, *start) + "' is digit\n", DEBUG, deep);
    } else {
        Logger::log("Result: '" + std::string(1, *start) + "' is not digit\n", DEBUG, deep);
    }

    return result;
}

bool SyntacticalAnalyzer::isUnsignedInteger(const char*& str, int deep) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;

    Logger::log("Function isUnsignedInteger() is called [deep=" + std::to_string(deep) + "]\n", DEBUG, deep);

    // Проверка наличия цифры на текущей и следующих позициях строки при помощи рекурсии.
    // При обнаружении очередной цифры с помощью функции isDigit, происходит сдвиг указателя на один
    // символ вперед. Таким образом считываются цифра числа, до тех пор, пока не встретится символ,
    // отличный от цифры.
    if (isDigit(str, deep + 1)) {
        isUnsignedInteger(str, deep + 1);
        result = true;
    }

    std::string number(start, str - start); // Найденное функцией беззнаковое число

    // Вывод результата
    if (result) {
        Logger::log("Result: '" + number + "' is unsigned integer\n", DEBUG, deep);
    } else {
        Logger::log("Result: '" + number + "' is not unsigned integer\n", DEBUG, deep);
    }

    return result;
}

bool SyntacticalAnalyzer::isInteger(const char*& str, int deep) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;

    Logger::log("Function isInteger() is called [deep=" + std::to_string(deep) + "]\n", DEBUG, deep);

    // Проверяем, что следующие символы в строке соответствуют одному из 3-ех вариантов:
    // 1) +беззнаковое_число
    // 2) -беззнаковое_число
    // 3) беззнаковое_число
    // При обнаружении любого из этих вариантов знаковое число считается найденным

    if (isChar(str, deep + 1, '+') || isChar(str, deep + 1, '-')) { // Проверка 1 и 2
        if (isUnsignedInteger(str, deep + 1)) {
            result = true;
        } else {
            str--;
        }
    } else { // Проверка 3
        result = isUnsignedInteger(str, deep + 1);
    }

    std::string number(start, str - start); // Найденное функцией знаковое число

    // Вывод результата
    if (result) {
        Logger::log("Result: '" + number + "' is integer\n", DEBUG, deep);
    } else {
        Logger::log("Result: '" + number + "' is not integer\n", DEBUG, deep);
    }

    return result;
}

bool SyntacticalAnalyzer::isRealNumber(const char*& str, int deep) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;

    Logger::log("Function isRealNumber() is called [deep=" + std::to_string(deep) + "]\n", DEBUG, deep);

    // Проверяем, что следующие символы в строке соответствуют одному из 3-ех вариантов:
    // 1) знаковое_число.беззнаковое_число
    // 2) знаковое_число.беззнаковое_числоEзнаковое_число
    // 3) знаковое_числоЕзнаковое_число
    // При обнаружении любого из этих вариантов действительное число считается найденным

    if (isInteger(str, deep + 1)) { // В начале обязательно должно стоять знаковое число
        if (isChar(str, deep + 1, '.')) { // Вариант 1 и 2
            if (isUnsignedInteger(str, deep + 1)) {
                result = true;
                if (isChar(str, deep + 1, 'E')) { // Вариант 2
                    result = isInteger(str, deep + 1);
                }
            }
        } else if (isChar(str, deep + 1, 'E')) { // Вариант 3
            result = isInteger(str, deep + 1);
        }
    }

    std::string number(start, str - start); // Найденное функцией действительное число

    // Вывод результата
    if (result) {
        Logger::log("Result: '" + number + "' is real\n", DEBUG, deep);
    } else {
        Logger::log("Result: '" + number + "' is not real\n", DEBUG, deep);
    }

    return result;
}

bool SyntacticalAnalyzer::analyze(const std::string& expression) {
    const char* end = expression.c_str(); // Получение С-style строки
    Logger::log("\n", DEBUG);
    bool result = isRealNumber(end, 0) && *end == '\0'; // Проверяем, что вся строка соответствует определению
    Logger::log("\n", DEBUG);
    return result;
}
