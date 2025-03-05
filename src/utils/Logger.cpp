// Logger.cpp
#include "Logger.h"

std::ofstream Logger::logFile;
std::mutex Logger::logMutex;
bool Logger::toFile = false;

std::string Logger::getTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void Logger::init(const std::string& filename) {
    if (!filename.empty()) {
        logFile.open(filename, std::ios::app);
        if (logFile.is_open()) {
            toFile = true;
        }
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::string logEntry = "[" + getTimestamp() + "] [" + logLevelToString(level) + "] " + message;

    if (toFile && logFile.is_open()) {
        logFile << logEntry << std::endl;
    }

    std::cout << logEntry << std::endl;
}

void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
