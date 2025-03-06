#include "ErrorHandler.h"
#include "Logger.h"
#include <iostream>
#include <stdexcept>

void ErrorHandler::reportError(const std::string& message, bool throwException) {
    Logger::log(LogLevel::ERROR, message); // Log the error message with appropriate log level

    if (throwException) {
        throw std::runtime_error(message); // Throw an exception if required
    } else {
        std::cerr << "Error: " << message << std::endl; // Print error to stderr
    }
}

void ErrorHandler::reportWarning(const std::string& message) {
    Logger::log(LogLevel::WARNING, message); // Log the warning message with appropriate log level
    std::cerr << "Warning: " << message << std::endl; // Print warning to stderr
}
