#include "ASTPrinter.h"
#include "ASTNode.h"  // Ensure ASTNode.h is included
#include <iostream>
#include <memory>

// Helper function to print indentation
void printIndent(int indent) {
    std::cout << std::string(indent, ' ');
}

void ASTPrinter::print(const std::shared_ptr<ASTNode>& node, int indent) {
    if (!node) {
        printIndent(indent);
        std::cout << "(null)" << std::endl;
        return;
    }

    printIndent(indent);
    std::cout << "└── " << node->toString() << std::endl;

    // Handle AST node types
    if (auto binaryExpr = std::dynamic_pointer_cast<BinaryExpressionNode>(node)) {
        print(binaryExpr->left, indent + 4);
        print(binaryExpr->right, indent + 4);
    }
    else if (auto funcCall = std::dynamic_pointer_cast<FunctionCallNode>(node)) {
        print(funcCall->functionName, indent + 4);
        for (const auto& arg : funcCall->arguments) {
            print(arg, indent + 8);
        }
    }
    else if (auto varDecl = std::dynamic_pointer_cast<VariableDeclarationNode>(node)) {
        print(varDecl->identifier, indent + 4);
        print(varDecl->initializer, indent + 4);
    }
    else if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclarationNode>(node)) {
        print(funcDecl->functionName, indent + 4);
        for (const auto& param : funcDecl->parameters) {
            print(param, indent + 8);
        }
        print(funcDecl->body, indent + 8);
    }
    else if (auto ifStmt = std::dynamic_pointer_cast<IfStatementNode>(node)) {
        print(ifStmt->condition, indent + 4);
        print(ifStmt->thenBlock, indent + 4);
        if (ifStmt->elseBlock) {
            print(ifStmt->elseBlock, indent + 4);
        }
    }
    else if (auto whileLoop = std::dynamic_pointer_cast<WhileLoopNode>(node)) {
        print(whileLoop->condition, indent + 4);
        print(whileLoop->body, indent + 4);
    }
    else if (auto block = std::dynamic_pointer_cast<BlockNode>(node)) {
        for (const auto& stmt : block->statements) {
            print(stmt, indent + 8);
        }
    }
    else if (auto returnStmt = std::dynamic_pointer_cast<ReturnStatementNode>(node)) {
        print(returnStmt->expression, indent + 4);
    }
}
