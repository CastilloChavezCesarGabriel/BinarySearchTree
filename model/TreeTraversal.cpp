#include "TreeTraversal.h"
#include <queue>

TreeTraversal::TreeTraversal() {}

void TreeTraversal::preOrder(Node* node, std::vector<float>& result) {
    if (node == nullptr) return;
    result.push_back(node->getValue());
    preOrder(node->getLeft(), result);
    preOrder(node->getRight(), result);
}

void TreeTraversal::inOrder(Node* node, std::vector<float>& result) {
    if (node == nullptr) return;
    inOrder(node->getLeft(), result);
    result.push_back(node->getValue());
    inOrder(node->getRight(), result);
}

void TreeTraversal::postOrder(Node* node, std::vector<float>& result) {
    if (node == nullptr) return;
    postOrder(node->getLeft(), result);
    postOrder(node->getRight(), result);
    result.push_back(node->getValue());
}

void TreeTraversal::levelOrder(Node* root, std::vector<float>& result) {
    if (root == nullptr) return;

    std::queue<Node*> node;
    node.push(root);

    while (!node.empty()) {
        Node* current = node.front();
        node.pop();

        result.push_back(current->getValue());

        if (current->getLeft()) {
            node.push(current->getLeft());
        }

        if (current->getRight()) {
            node.push(current->getRight());
        }
    }
}
