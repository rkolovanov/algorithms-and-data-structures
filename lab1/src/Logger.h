#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>


enum MessageType {
    COMMON,
    DEBUG
};


class Logger {
    int indentSize_ = 4; 
    bool silentMode_ = false;
    bool fileOutput_ = false;
    std::string filePath_;
    std::ofstream file_;

    Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger();

public:
    static Logger& getInstance();
    static void log(const std::string& message, MessageType type = COMMON, int indents = 0);
    void setSilentMode(bool value);
    void setFileOutput(const std::string& filePath);
};


#endif // LOGGER_H
