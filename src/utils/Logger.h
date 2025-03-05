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
    // Initializes the logger with an optional file output
    static void init(const std::string& filename = "");

    // Logs a message with the given level
    static void log(LogLevel level, const std::string& message);

    // Closes the log file if it was opened
    static void close();

private:
    static std::ofstream logFile;
    static std::mutex logMutex;
    static bool useFile;

    // Helper function to convert log level to string
    static std::string levelToString(LogLevel level);

    // Helper function to get formatted timestamp
    static std::string getTimestamp();
};

#endif // LOGGER_H
