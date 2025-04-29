#ifndef TREETRANSVERSAL_H
#define TREETRANSVERSAL_H
#include "Node.h"
#include <vector>

class TreeTransversal {
public:
    TreeTransversal();
    static void preOrder(Node* node, std::vector<float>& result);
    static void inOrder(Node* node, std::vector<float>& result);
    static void postOrder(Node* node, std::vector<float>& result);
};

#endif //TREETRANSVERSAL_H
