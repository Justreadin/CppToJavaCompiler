#include "Logger.h"
#include <iostream>
#include <ctime>

std::ofstream Logger::logFile;
std::mutex Logger::logMutex;
bool Logger::useFile = false;

std::string Logger::getTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

std::string Logger::levelToString(LogLevel level) {
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
            useFile = true;
        }
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::string logEntry = "[" + getTimestamp() + "] [" + levelToString(level) + "] " + message;

    if (useFile && logFile.is_open()) {
        logFile << logEntry << std::endl;
    }

    std::cout << logEntry << std::endl;
}

void Logger::logError(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::logWarning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
