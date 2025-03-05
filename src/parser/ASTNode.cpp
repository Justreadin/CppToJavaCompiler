#include "ASTNode.h"

// Constructor for base ASTNode
ASTNode::ASTNode(NodeType type) : type(type) {}

// Convert enum NodeType to string
std::string ASTNode::nodeTypeToString(NodeType type) {
    switch (type) {
        case NodeType::PROGRAM: return "PROGRAM";
        case NodeType::FUNCTION_DECLARATION: return "FUNCTION_DECLARATION";
        case NodeType::VARIABLE_DECLARATION: return "VARIABLE_DECLARATION";
        case NodeType::BINARY_EXPRESSION: return "BINARY_EXPRESSION";
        case NodeType::IDENTIFIER: return "IDENTIFIER";
        case NodeType::NUMBER_LITERAL: return "NUMBER_LITERAL";
        case NodeType::STRING_LITERAL: return "STRING_LITERAL";
        case NodeType::RETURN_STATEMENT: return "RETURN_STATEMENT";
        case NodeType::FUNCTION_CALL: return "FUNCTION_CALL";
        case NodeType::IF_STATEMENT: return "IF_STATEMENT";
        case NodeType::WHILE_LOOP: return "WHILE_LOOP";
        case NodeType::BLOCK: return "BLOCK";
        default: return "UNKNOWN";
    }
}

// ---------------------------------
// IdentifierNode Implementation
// ---------------------------------
IdentifierNode::IdentifierNode(const std::string& name)
    : ASTNode(NodeType::IDENTIFIER), name(name) {}

std::string IdentifierNode::toString() const {
    return "Identifier(" + name + ")";
}

// ---------------------------------
// NumberNode Implementation
// ---------------------------------
NumberNode::NumberNode(double value)
    : ASTNode(NodeType::NUMBER_LITERAL), value(value) {}

std::string NumberNode::toString() const {
    return "Number(" + std::to_string(value) + ")";
}

// ---------------------------------
// StringNode Implementation
// ---------------------------------
StringNode::StringNode(const std::string& value)
    : ASTNode(NodeType::STRING_LITERAL), value(value) {}

std::string StringNode::toString() const {
    return "String(\"" + value + "\")";
}

// ---------------------------------
// BinaryExpressionNode Implementation
// ---------------------------------
BinaryExpressionNode::BinaryExpressionNode(std::shared_ptr<ASTNode> left, const std::string& op, std::shared_ptr<ASTNode> right)
    : ASTNode(NodeType::BINARY_EXPRESSION), left(left), op(op), right(right) {}

std::string BinaryExpressionNode::toString() const {
    return "BinaryExpression(" + left->toString() + " " + op + " " + right->toString() + ")";
}

// ---------------------------------
// FunctionCallNode Implementation
// ---------------------------------
FunctionCallNode::FunctionCallNode(std::shared_ptr<ASTNode> functionName, std::vector<std::shared_ptr<ASTNode>> arguments)
    : ASTNode(NodeType::FUNCTION_CALL), functionName(functionName), arguments(arguments) {}

std::string FunctionCallNode::toString() const {
    std::string result = "FunctionCall(" + functionName->toString() + "(";
    for (size_t i = 0; i < arguments.size(); ++i) {
        result += arguments[i]->toString();
        if (i < arguments.size() - 1)
            result += ", ";
    }
    result += "))";
    return result;
}

// ---------------------------------
// VariableDeclarationNode Implementation
// ---------------------------------
VariableDeclarationNode::VariableDeclarationNode(const std::string& type, std::shared_ptr<ASTNode> identifier, std::shared_ptr<ASTNode> initializer)
    : ASTNode(NodeType::VARIABLE_DECLARATION), type(type), identifier(identifier), initializer(initializer) {}

std::string VariableDeclarationNode::toString() const {
    return "VariableDeclaration(" + type + " " + identifier->toString() + " = " + (initializer ? initializer->toString() : "null") + ")";
}

// ---------------------------------
// FunctionDeclarationNode Implementation
// ---------------------------------
FunctionDeclarationNode::FunctionDeclarationNode(const std::string& returnType, std::shared_ptr<ASTNode> functionName,
                                                 std::vector<std::shared_ptr<ASTNode>> parameters, std::shared_ptr<ASTNode> body)
    : ASTNode(NodeType::FUNCTION_DECLARATION), returnType(returnType), functionName(functionName), parameters(parameters), body(body) {}

std::string FunctionDeclarationNode::toString() const {
    std::string result = "FunctionDeclaration(" + returnType + " " + functionName->toString() + "(";
    for (size_t i = 0; i < parameters.size(); ++i) {
        result += parameters[i]->toString();
        if (i < parameters.size() - 1)
            result += ", ";
    }
    result += ") " + (body ? body->toString() : "null") + ")";
    return result;
}

// ---------------------------------
// ReturnStatementNode Implementation
// ---------------------------------
ReturnStatementNode::ReturnStatementNode(std::shared_ptr<ASTNode> expression)
    : ASTNode(NodeType::RETURN_STATEMENT), expression(expression) {}

std::string ReturnStatementNode::toString() const {
    return "Return(" + (expression ? expression->toString() : "null") + ")";
}

// ---------------------------------
// IfStatementNode Implementation
// ---------------------------------
IfStatementNode::IfStatementNode(std::shared_ptr<ASTNode> condition, std::shared_ptr<ASTNode> thenBlock, std::shared_ptr<ASTNode> elseBlock)
    : ASTNode(NodeType::IF_STATEMENT), condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {}

std::string IfStatementNode::toString() const {
    return "If(" + condition->toString() + " then " + thenBlock->toString() + (elseBlock ? " else " + elseBlock->toString() : "") + ")";
}

// ---------------------------------
// WhileLoopNode Implementation
// ---------------------------------
WhileLoopNode::WhileLoopNode(std::shared_ptr<ASTNode> condition, std::shared_ptr<ASTNode> body)
    : ASTNode(NodeType::WHILE_LOOP), condition(condition), body(body) {}

std::string WhileLoopNode::toString() const {
    return "While(" + condition->toString() + " " + body->toString() + ")";
}

// ---------------------------------
// BlockNode Implementation
// ---------------------------------
BlockNode::BlockNode(std::vector<std::shared_ptr<ASTNode>> statements)
    : ASTNode(NodeType::BLOCK), statements(statements) {}

std::string BlockNode::toString() const {
    std::string result = "Block({ ";
    for (size_t i = 0; i < statements.size(); ++i) {
        result += statements[i]->toString();
        if (i < statements.size() - 1)
            result += "; ";
    }
    result += " })";
    return result;
}
