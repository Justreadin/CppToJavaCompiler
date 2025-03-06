#include "CodeGenerator.h"
#include <iostream>

CodeGenerator::CodeGenerator(JavaEmitter& emitter) : emitter(emitter) {}

void CodeGenerator::generateCode(const ASTNodePtr& root) {
    if (!root) {
        std::cerr << "Error: Cannot generate code for a null AST.\n";
        return;
    }

    generateStatement(root);
}

void CodeGenerator::generateStatement(const ASTNodePtr& node) {
    if (!node) return;

    switch (node->type) {
        case NodeType::VARIABLE_DECLARATION:
            emitter.emitVariableDeclaration(node);
            break;

        case NodeType::FUNCTION_DECLARATION:
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

        case NodeType::BLOCK: {
            auto blockNode = std::dynamic_pointer_cast<BlockNode>(node);
            if (!blockNode) return;
            for (const auto& stmt : blockNode->statements) {
                generateStatement(stmt);
            }
            break;
        }

        default:
            generateExpression(node);
            break;
    }
}

void CodeGenerator::generateExpression(const ASTNodePtr& node) {
    if (!node) return;

    switch (node->type) {
        case NodeType::BINARY_EXPRESSION:
            emitter.emitBinaryExpression(node);
            break;

        case NodeType::IDENTIFIER:
        case NodeType::NUMBER_LITERAL:
        case NodeType::STRING_LITERAL:
            emitter.emitExpression(node);
            break;

        case NodeType::FUNCTION_CALL:
            emitter.emitFunctionCall(node);
            break;

        default:
            std::cerr << "Warning: Unsupported expression type encountered.\n";
            break;
    }
}
