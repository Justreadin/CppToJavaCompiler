#include "OutputWriter.h"
#include <iostream>

OutputWriter::OutputWriter(const std::string& filename) {
    outFile.open(filename);
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }
}

OutputWriter::~OutputWriter() {
    close();  // Ensure the file is closed when object is destroyed
}

void OutputWriter::write(const std::string& line) {
    if (outFile.is_open()) {
        outFile << line << std::endl;
    } else {
        std::cerr << "Error: Attempted to write to a closed file." << std::endl;
    }
}

void OutputWriter::close() {
    if (outFile.is_open()) {
        outFile.close();
    }
}
