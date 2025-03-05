#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>
#include <stdexcept>

class ErrorHandler {
public:
    // Logs an error message and optionally throws an exception
    static void reportError(const std::string& message, bool throwException = false);

    // Logs a warning message
    static void reportWarning(const std::string& message);
};

#endif // ERRORHANDLER_H
