#include "SymbolTable.h"
#include <iostream>

// Add or update a symbol (variable or function)
void SymbolTable::addSymbol(const std::string& name, const std::string& type) {
    symbols[name] = type;
}

// Check if a symbol is defined
bool SymbolTable::isDefined(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

// Get the type of a symbol; return an empty string if not found
std::string SymbolTable::getType(const std::string& name) const {
    return isDefined(name) ? symbols.at(name) : "";
}

// Update an existing symbol’s type
void SymbolTable::setType(const std::string& name, const std::string& type) {
    if (isDefined(name)) {
        symbols[name] = type;
    }
}

// Remove a symbol (used for scoping)
void SymbolTable::removeSymbol(const std::string& name) {
    symbols.erase(name);
}

// Debug function to print the symbol table
void SymbolTable::print() const {
    std::cout << "Symbol Table:\n";
    for (const auto& entry : symbols) {
        std::cout << "  " << entry.first << " -> " << entry.second << std::endl;
    }
}
