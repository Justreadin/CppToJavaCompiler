#include "OutputWriter.h"
#include <iostream>
#include <stdexcept>

OutputWriter::OutputWriter(const std::string& filename) : outFile(filename) {
    if (!outFile) {
        throw std::runtime_error("Failed to open output file: " + filename);
    }
}

OutputWriter::~OutputWriter() {
    close(); // Ensure the file is closed properly
}

bool OutputWriter::isOpen() const {
    // Implement actual logic if needed
    return true;
}


void OutputWriter::write(const std::string& line) {
    contents += line + "\n";  // Store an in-memory copy
    if (outFile.is_open()) {
        outFile << line << std::endl;
    } else {
        throw std::runtime_error("Attempted to write to a closed file.");
    }
}

std::string OutputWriter::getContents() const {
    return contents;  // Return the stored Java code
}

void OutputWriter::close() {
    if (outFile.is_open()) {
        outFile.close();
    }
}
