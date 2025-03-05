#ifndef ASTNODE_H
#define ASTNODE_H

#include <memory>
#include <vector>
#include <string>

// Enum for node types
enum class NodeType {
    PROGRAM,
    FUNCTION_DECLARATION,
    VARIABLE_DECLARATION,
    BINARY_EXPRESSION,  // Ensure this is defined
    IDENTIFIER,
    NUMBER_LITERAL,  // Ensure this is defined
    STRING_LITERAL,
    RETURN_STATEMENT,
    FUNCTION_CALL,
    IF_STATEMENT,
    WHILE_LOOP,
    BLOCK
};

// Abstract base class for all AST nodes
class ASTNode {
public:
    NodeType type;

    explicit ASTNode(NodeType type);
    virtual ~ASTNode() = default;
    virtual std::string toString() const = 0;

    static std::string nodeTypeToString(NodeType type);
};

// Node for identifiers (variables, function names)
class IdentifierNode : public ASTNode {
public:
    std::string name;
    explicit IdentifierNode(const std::string& name);

    std::string toString() const override;
};

// Node for numeric literals
class NumberNode : public ASTNode {
public:
    double value;
    explicit NumberNode(double value);

    std::string toString() const override;
};

// Node for string literals
class StringNode : public ASTNode {
public:
    std::string value;
    explicit StringNode(const std::string& value);

    std::string toString() const override;
};

// Node for binary expressions (e.g., a + b)
class BinaryExpressionNode : public ASTNode {
public:
    std::shared_ptr<ASTNode> left;
    std::string op;
    std::shared_ptr<ASTNode> right;

    BinaryExpressionNode(std::shared_ptr<ASTNode> left, const std::string& op, std::shared_ptr<ASTNode> right);
    std::string toString() const override;
};

// Node for function calls (e.g., foo(1, "test"))
class FunctionCallNode : public ASTNode {
public:
    std::shared_ptr<ASTNode> functionName;
    std::vector<std::shared_ptr<ASTNode>> arguments;

    FunctionCallNode(std::shared_ptr<ASTNode> functionName, std::vector<std::shared_ptr<ASTNode>> arguments);
    std::string toString() const override;
};

// Node for variable declarations (e.g., int x = 5;)
class VariableDeclarationNode : public ASTNode {
public:
    std::string type;
    std::shared_ptr<ASTNode> identifier;
    std::shared_ptr<ASTNode> initializer;

    VariableDeclarationNode(const std::string& type, std::shared_ptr<ASTNode> identifier, std::shared_ptr<ASTNode> initializer);
    std::string toString() const override;
};

// Node for function declarations
class FunctionDeclarationNode : public ASTNode {
public:
    std::string returnType;
    std::shared_ptr<ASTNode> functionName;
    std::vector<std::shared_ptr<ASTNode>> parameters;
    std::shared_ptr<ASTNode> body;

    FunctionDeclarationNode(const std::string& returnType, std::shared_ptr<ASTNode> functionName,
                            std::vector<std::shared_ptr<ASTNode>> parameters, std::shared_ptr<ASTNode> body);
    std::string toString() const override;
};

// Node for return statements
class ReturnStatementNode : public ASTNode {
public:
    std::shared_ptr<ASTNode> expression;

    explicit ReturnStatementNode(std::shared_ptr<ASTNode> expression);
    std::string toString() const override;
};

// Node for conditional (if) statements
class IfStatementNode : public ASTNode {
public:
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> thenBlock;
    std::shared_ptr<ASTNode> elseBlock;

    IfStatementNode(std::shared_ptr<ASTNode> condition, std::shared_ptr<ASTNode> thenBlock, std::shared_ptr<ASTNode> elseBlock);
    std::string toString() const override;
};

// Node for while loops
class WhileLoopNode : public ASTNode {
public:
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> body;

    WhileLoopNode(std::shared_ptr<ASTNode> condition, std::shared_ptr<ASTNode> body);
    std::string toString() const override;
};

// Node for block statements { ... }
class BlockNode : public ASTNode {
public:
    std::vector<std::shared_ptr<ASTNode>> statements;

    explicit BlockNode(std::vector<std::shared_ptr<ASTNode>> statements);
    std::string toString() const override;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

#endif // ASTNODE_H
