#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Reads the entire file content as a single string
std::string FileReader::readFileAsString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Reads the file line by line into a vector of strings
std::vector<std::string> FileReader::readFileLines(const std::string& filePath) {
    std::ifstream file(filePath);
    std::vector<std::string> lines;
    if (!file) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return lines;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}
