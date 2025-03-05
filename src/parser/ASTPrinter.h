#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "ASTNode.h"
#include <memory>

class ASTPrinter {
public:
    static void print(const std::shared_ptr<ASTNode>& node, int indent = 0);
};

#endif // ASTPRINTER_H
