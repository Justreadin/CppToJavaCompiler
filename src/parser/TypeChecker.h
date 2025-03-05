#ifndef TYPECHECKER_H
#define TYPECHECKER_H

#include "ASTNode.h"
#include "SymbolTable.h"
#include <string>
#include <vector>

class TypeChecker {
public:
    // Checks the types in the AST and accumulates errors instead of failing on the first one
    static bool check(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors);

private:
    // Infers the type of an AST node
    static std::string inferType(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors);

    // Helper function to check binary expressions
    static bool checkBinaryExpression(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors);

    // Helper function to check function calls
    static bool checkFunctionCall(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors);

    // Helper function to check variable assignments
    static bool checkAssignment(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors);
};

#endif // TYPECHECKER_H
