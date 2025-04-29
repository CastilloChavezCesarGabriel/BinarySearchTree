#include "TreeTransversal.h"

TreeTransversal::TreeTransversal() {}

void TreeTransversal::preOrder(Node* node, std::vector<float>& result) {
    if (node == nullptr) return;
    result.push_back(node->getValue());
    preOrder(node->getLeft(), result);
    preOrder(node->getRight(), result);
}

void TreeTransversal::inOrder(Node* node, std::vector<float>& result) {
    if (node == nullptr) return;
    inOrder(node->getLeft(), result);
    result.push_back(node->getValue());
    inOrder(node->getRight(), result);
}

void TreeTransversal::postOrder(Node* node, std::vector<float>& result) {
    if (node == nullptr) return;
    postOrder(node->getLeft(), result);
    postOrder(node->getRight(), result);
    result.push_back(node->getValue());
}
