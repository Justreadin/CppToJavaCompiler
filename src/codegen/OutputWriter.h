#ifndef OUTPUTWRITER_H
#define OUTPUTWRITER_H

#include <string>
#include <fstream>

class OutputWriter {
private:
    std::ofstream outFile;
    std::string contents;   // ✅ Store generated code in memory

public:
    OutputWriter(const std::string& filename);
    ~OutputWriter();

    void write(const std::string& line);
    std::string getContents() const; // ✅ Method to retrieve generated Java code

    bool isOpen() const; // Declare the function
    void close();
};

#endif // OUTPUTWRITER_H
