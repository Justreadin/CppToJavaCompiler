#include "TypeChecker.h"
#include <iostream>

// Recursively check the types in the AST
bool TypeChecker::check(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors) {
    if (!node) return false;

    switch (node->type) {
        case NodeType::VARIABLE_DECLARATION: {
            auto varDecl = std::dynamic_pointer_cast<VariableDeclarationNode>(node);
            if (!varDecl) return false;

            std::string varName = varDecl->identifier;
            std::string varType = varDecl->varType;  // Assuming the correct member is `varType`

            if (table.isDefined(varName)) {
                errors.push_back("Error: Variable '" + varName + "' is already declared.");
                return false;
            }

            table.addSymbol(varName, varType);
            break;
        }
        case NodeType::BINARY_EXPRESSION:
            return checkBinaryExpression(node, table, errors);

        case NodeType::FUNCTION_CALL:
            return checkFunctionCall(node, table, errors);

        case NodeType::RETURN_STATEMENT: {
            auto returnStmt = std::dynamic_pointer_cast<ReturnStatementNode>(node);
            if (!returnStmt) return false;

            std::string returnType = inferType(returnStmt->expression, table, errors);
            if (returnType == "UNKNOWN") {
                errors.push_back("Error: Invalid return statement type.");
                return false;
            }
            break;
        }
        case NodeType::IF_STATEMENT: {
            auto ifStmt = std::dynamic_pointer_cast<IfStatementNode>(node);
            if (!ifStmt) return false;

            std::string condType = inferType(ifStmt->condition, table, errors);
            if (condType != "bool") {
                errors.push_back("Error: If statement condition must be a boolean.");
                return false;
            }

            check(ifStmt->thenBlock, table, errors);
            if (ifStmt->elseBlock) check(ifStmt->elseBlock, table, errors);
            break;
        }
        case NodeType::WHILE_LOOP: {
            auto whileLoop = std::dynamic_pointer_cast<WhileLoopNode>(node);
            if (!whileLoop) return false;

            std::string condType = inferType(whileLoop->condition, table, errors);
            if (condType != "bool") {
                errors.push_back("Error: While loop condition must be a boolean.");
                return false;
            }

            check(whileLoop->body, table, errors);
            break;
        }
        case NodeType::BLOCK: {
            auto block = std::dynamic_pointer_cast<BlockNode>(node);
            if (!block) return false;
            for (const auto& stmt : block->statements) {
                check(stmt, table, errors);
            }
            break;
        }
        default:
            return false;
    }

    return true;
}

// Infer the type of an AST node
std::string TypeChecker::inferType(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors) {
    if (!node) return "UNKNOWN";

    switch (node->type) {
        case NodeType::NUMBER_LITERAL:
            return "int";
        case NodeType::STRING_LITERAL:
            return "string";
        case NodeType::IDENTIFIER: {
            auto idNode = std::dynamic_pointer_cast<IdentifierNode>(node);
            if (!idNode) return "UNKNOWN";
            return table.getType(idNode->identifier);
        }
        case NodeType::BINARY_EXPRESSION:
            return checkBinaryExpression(node, table, errors) ? inferType(node, table, errors) : "UNKNOWN";
        case NodeType::FUNCTION_CALL: {
            auto funcCall = std::dynamic_pointer_cast<FunctionCallNode>(node);
            if (!funcCall) return "UNKNOWN";
            return table.getType(funcCall->functionName);
        }
        default:
            return "UNKNOWN";
    }
}

// Checks type consistency in binary expressions
bool TypeChecker::checkBinaryExpression(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors) {
    auto binExpr = std::dynamic_pointer_cast<BinaryExpressionNode>(node);
    if (!binExpr) return false;

    std::string leftType = inferType(binExpr->left, table, errors);
    std::string rightType = inferType(binExpr->right, table, errors);

    if (leftType != rightType) {
        errors.push_back("Type Error: Mismatched types in binary expression (" + leftType + " vs. " + rightType + ").");
        return false;
    }

    return true;
}

// Checks function call argument types
bool TypeChecker::checkFunctionCall(ASTNodePtr node, SymbolTable& table, std::vector<std::string>& errors) {
    auto funcCall = std::dynamic_pointer_cast<FunctionCallNode>(node);
    if (!funcCall) return false;

    std::string functionName = funcCall->functionName;
    if (!table.isDefined(functionName)) {
        errors.push_back("Error: Function '" + functionName + "' is not declared.");
        return false;
    }

    for (const auto& arg : funcCall->arguments) {
        std::string argType = inferType(arg, table, errors);
        if (argType == "UNKNOWN") {
            errors.push_back("Error: Invalid argument type in function call to '" + functionName + "'.");
            return false;
        }
    }

    return true;
}
