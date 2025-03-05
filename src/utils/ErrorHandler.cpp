#include "ErrorHandler.h"
#include "Logger.h"
#include <iostream>
#include <stdexcept>

void ErrorHandler::reportError(const std::string& message, bool throwException) {
    Logger::logError(message); // Log the error message

    if (throwException) {
        throw std::runtime_error(message); // Throw an exception if required
    } else {
        std::cerr << "Error: " << message << std::endl; // Print error to stderr
    }
}

void ErrorHandler::reportWarning(const std::string& message) {
    Logger::logWarning(message); // Log the warning message
    std::cerr << "Warning: " << message << std::endl; // Print warning to stderr
}
