#include "CodeGenerator.h"
#include <iostream>

CodeGenerator::CodeGenerator(JavaEmitter& emitter) : emitter(emitter) {}

void CodeGenerator::generateCode(const ASTNodePtr& root) {
    if (!root) {
        std::cerr << "Error: Cannot generate code for a null AST.\n";
        return;
    }

    for (const auto& child : root->children) {
        generateStatement(child);
    }
}

void CodeGenerator::generateStatement(const ASTNodePtr& node) {
    if (!node) return;

    switch (node->type) {
        case NodeType::VARIABLE_DECL:
            emitter.emitVariableDeclaration(node);
            break;

        case NodeType::FUNCTION_DECL:
            emitter.emitFunction(node);
            break;

        case NodeType::RETURN_STATEMENT:
            emitter.emitReturn(node);
            break;

        case NodeType::IF_STATEMENT:
            emitter.emitIfStatement(node);
            break;

        case NodeType::WHILE_LOOP:
            emitter.emitWhileLoop(node);
            break;

        default:
            generateExpression(node);
            break;
    }
}

void CodeGenerator::generateExpression(const ASTNodePtr& node) {
    if (!node) return;

    switch (node->type) {
        case NodeType::BINARY_EXPR:
            emitter.emitBinaryExpression(node);
            break;

        case NodeType::IDENTIFIER:
        case NodeType::NUMBER:
            emitter.emitExpression(node);
            break;

        default:
            std::cerr << "Warning: Unsupported expression type encountered.\n";
            break;
    }
}
