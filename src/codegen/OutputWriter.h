#ifndef OUTPUTWRITER_H
#define OUTPUTWRITER_H

#include <string>
#include <fstream>

class OutputWriter {
private:
    std::ofstream outFile;  // Declare output file stream

public:
    OutputWriter(const std::string& filename);
    ~OutputWriter();

    void write(const std::string& line);
    void close();
};

#endif // OUTPUTWRITER_H
