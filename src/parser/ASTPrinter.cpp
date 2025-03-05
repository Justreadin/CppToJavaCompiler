#include "ASTPrinter.h"
#include "ASTNode.h"
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

    switch (node->type) {
        case NodeType::BINARY_EXPRESSION: {
            auto binaryExpr = std::static_pointer_cast<BinaryExpressionNode>(node);
            print(binaryExpr->left, indent + 4);
            printIndent(indent + 2);
            std::cout << "Operator: " << binaryExpr->op << std::endl;
            print(binaryExpr->right, indent + 4);
            break;
        }
        case NodeType::FUNCTION_CALL: {
            auto funcCall = std::static_pointer_cast<FunctionCallNode>(node);
            print(funcCall->functionName, indent + 4);
            for (const auto& arg : funcCall->arguments) {
                print(arg, indent + 8);
            }
            break;
        }
        case NodeType::VARIABLE_DECLARATION: {
            auto varDecl = std::static_pointer_cast<VariableDeclarationNode>(node);
            printIndent(indent + 4);
            std::cout << "Type: " << varDecl->type << std::endl;
            print(varDecl->identifier, indent + 4);
            if (varDecl->initializer) {
                print(varDecl->initializer, indent + 4);
            }
            break;
        }
        case NodeType::FUNCTION_DECLARATION: {
            auto funcDecl = std::static_pointer_cast<FunctionDeclarationNode>(node);
            printIndent(indent + 4);
            std::cout << "Return Type: " << funcDecl->returnType << std::endl;
            print(funcDecl->functionName, indent + 4);
            for (const auto& param : funcDecl->parameters) {
                print(param, indent + 8);
            }
            print(funcDecl->body, indent + 8);
            break;
        }
        case NodeType::RETURN_STATEMENT: {
            auto returnStmt = std::static_pointer_cast<ReturnStatementNode>(node);
            print(returnStmt->expression, indent + 4);
            break;
        }
        case NodeType::IF_STATEMENT: {
            auto ifStmt = std::static_pointer_cast<IfStatementNode>(node);
            print(ifStmt->condition, indent + 4);
            print(ifStmt->thenBlock, indent + 4);
            if (ifStmt->elseBlock) {
                print(ifStmt->elseBlock, indent + 4);
            }
            break;
        }
        case NodeType::WHILE_LOOP: {
            auto whileLoop = std::static_pointer_cast<WhileLoopNode>(node);
            print(whileLoop->condition, indent + 4);
            print(whileLoop->body, indent + 4);
            break;
        }
        case NodeType::BLOCK: {
            auto block = std::static_pointer_cast<BlockNode>(node);
            for (const auto& stmt : block->statements) {
                print(stmt, indent + 8);
            }
            break;
        }
        case NodeType::IDENTIFIER: {
            auto identifier = std::static_pointer_cast<IdentifierNode>(node);
            printIndent(indent + 4);
            std::cout << "Identifier: " << identifier->name << std::endl;
            break;
        }
        case NodeType::NUMBER_LITERAL: {
            auto number = std::static_pointer_cast<NumberNode>(node);
            printIndent(indent + 4);
            std::cout << "Number: " << number->value << std::endl;
            break;
        }
        case NodeType::STRING_LITERAL: {
            auto strNode = std::static_pointer_cast<StringNode>(node);
            printIndent(indent + 4);
            std::cout << "String: \"" << strNode->value << "\"" << std::endl;
            break;
        }
        default:
            printIndent(indent + 4);
            std::cout << "(Unknown node type)" << std::endl;
            break;
    }
}
