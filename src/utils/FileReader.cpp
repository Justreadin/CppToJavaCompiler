#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Logger.h"

// Reads the entire file content as a single string
std::string FileReader::readFileAsString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        Logger::logError("Error: Unable to open file " + filePath);
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Reads the file line by line into a vector of strings
std::vector<std::string> FileReader::readFileAsLines(const std::string& filePath) {  // Fixed function name
    std::ifstream file(filePath);
    std::vector<std::string> lines;
    if (!file) {
        Logger::logError("Error: Unable to open file " + filePath);
        return lines;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}
