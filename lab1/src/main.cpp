#include <iostream>
#include <fstream>

void log(std::string message, std::ofstream& file, int indent = 0) {
    std::cout << std::string(4 * indent, ' ') << message; // Вывод на консоль
    file << std::string(4 * indent, ' ') << message; // Вывод в файл
}

//        { 1, если n = 1
// f(n) = {
//        { f(n / 2) + f(n / 3) + ... + f(n / n), если n >= 2

int f(int n, std::ofstream& file, int deep = 0) {
    if (n == 1) { // При n == 1
        log("Вызов f(1): f(1) = 1\n", file, deep);
        return 1;
    }

    // При n >= 2
    int sum = 0; 
    log("Вызов f(" + std::to_string(n) + "):\n", file, deep);

    for (int i = 2; i <= n; i++) {
        sum += f(n / i, file, deep + 1);
    }

    log("Значение функции f(" + std::to_string(n) + ") = " + std::to_string(sum) + "\n\n", file, deep);
    return sum;
}

int main() {
    char selectedAction; // Выбранное действие
    int results[16]; // Результаты функции f
    std::ofstream file("log.txt"); // Открытие файла на чтение

    log("Доступные действия:\n\n\t[Цифра 0] Рассчитать значения рекурсивной функции f для аргументов 15, ... , 30.\n", file);
    log("\t[Цифра 1] Ввести свой аргумент для рекурсивной функции f.\n", file);
    log("\t[Остальное] Выйти из программы.\n\n", file);

    // Считывание выбранного действия
    std::cout << "[Выберите действие] ";
    std::cin >> selectedAction;

    log("Выбранное действие: " + std::string(1, selectedAction) + "\n\n", file);

    if (selectedAction == '0') {
        // Вычисление значения функции для аргументов 15, ... , 30
        for (int i = 15; i <= 30; i++) {
            log("[ Вычислние значения функции f с аргументом " + std::to_string(i) + " ]\n\n", file);
            results[i - 15] = f(i, file);
            log("\n", file);
        }

        // Вывод значений функции
        log("Результаты:\n\n", file);
        for (int i = 0; i < 16; i++) {
            log("    f(" + std::to_string(i + 15) + ") = " + std::to_string(results[i]) + "\n", file);
        }
        log("\n", file);

    } else if (selectedAction == '1') {
        int arg = -1;

        // Ввод аргумента (до тех пор, пока пользователь не введет корректный аргумент)
        while (arg < 1) {
            std::cout << "[Введите аргумент (должен быть целым и положительным числом)] ";
            std::cin >> arg;

            // Очищаем поток ввода до символа перевода строки
            if (std::cin.fail()) {
                std::cin.clear();
                while (std::cin.get() != '\n');
            }
        }

        // Вывод результата работы функции
        log("Введенный аргумент: " + std::to_string(arg) + "\n", file);
        int result = f(arg, file);
        log("Результат: f(" + std::to_string(arg) + ") = " + std::to_string(result) + "\n", file);
    }

    return 0;
}
