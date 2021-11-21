#ifndef INODE_H
#define INODE_H
#include "interpreter.h"

class INode
{
public:
    INode();
    void accept(Interpreter visitor);
};

#endif // INODE_H
