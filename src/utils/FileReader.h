#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

class FileReader {
public:
    // Reads the entire file as a single string
    static std::string readFileAsString(const std::string& filePath);

    // Reads the file line by line and returns a vector of lines
    static std::vector<std::string> readFileAsLines(const std::string& filePath);
};

#endif // FILEREADER_H
