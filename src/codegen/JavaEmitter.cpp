#include "JavaEmitter.h"
#include <iostream>

JavaEmitter::JavaEmitter(OutputWriter& writer) : writer(writer) {}

void JavaEmitter::emitVariableDeclaration(const ASTNodePtr& node) {
    if (!node || node->children.empty()) return;

    std::string type = "int"; // Default to int for now, later improve type inference
    std::string name = node->children[0]->toString();
    std::string value = node->children.size() > 1 ? node->children[1]->toString() : "";

    writer.write(type + " " + name + (value.empty() ? ";" : " = " + value + ";"));
}

void JavaEmitter::emitFunction(const ASTNodePtr& node) {
    if (!node || node->children.size() < 2) return;

    std::string returnType = "void"; // Default, refine based on AST
    std::string functionName = node->children[0]->toString();

    writer.write(returnType + " " + functionName + "() {");

    for (size_t i = 1; i < node->children.size(); ++i) {
        emitExpression(node->children[i]);
    }

    writer.write("}");
}

void JavaEmitter::emitReturn(const ASTNodePtr& node) {
    if (!node || node->children.empty()) return;

    writer.write("return " + node->children[0]->toString() + ";");
}

void JavaEmitter::emitBinaryExpression(const ASTNodePtr& node) {
    if (!node || node->children.size() < 2) return;

    std::string left = node->children[0]->toString();
    std::string op = node->toString();
    std::string right = node->children[1]->toString();

    writer.write(left + " " + op + " " + right);
}

void JavaEmitter::emitExpression(const ASTNodePtr& node) {
    if (!node) return;

    writer.write(node->toString() + ";");
}
