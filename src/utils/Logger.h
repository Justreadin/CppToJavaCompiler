#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static void init(const std::string& filename = "");
    static void log(LogLevel level, const std::string& message);
    static void logError(const std::string& message);
    static void logWarning(const std::string& message);
    static void close();

private:
    static std::ofstream logFile;
    static std::mutex logMutex;
    static bool useFile;

    static std::string levelToString(LogLevel level);
    static std::string getTimestamp();
};

#endif // LOGGER_H
