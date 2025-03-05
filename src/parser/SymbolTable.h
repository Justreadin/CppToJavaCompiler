#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>

class SymbolTable {
private:
    std::unordered_map<std::string, std::string> symbols; // Variable name -> type mapping

public:
    // Define or update a variable
    void addSymbol(const std::string& name, const std::string& type);

    // Check if a variable is already declared
    bool isDefined(const std::string& name) const;

    // Get the type of a variable (returns empty string if undefined)
    std::string getType(const std::string& name) const;

    // Update the type of an existing variable
    void setType(const std::string& name, const std::string& type);

    // Remove a symbol (for scoping purposes)
    void removeSymbol(const std::string& name);

    // Debug function to print symbol table
    void print() const;
};

#endif // SYMBOLTABLE_H
