#include "Model.h"

Model::Model() {}

Node* Model::getRoot() const {
    return tree.getRoot();
}

void Model::setRoot(Node* newRoot) {
    tree.setRoot(newRoot);
}

bool Model::isNodeExist(const float& value) const {
    return findNode(value) != nullptr;
}

void Model::createRoot(const float& value) {
    if (!getRoot()) {
       setRoot(new Node(value));
    }
}

void Model::createNode(Node* parent, const bool isLeft, const float& value) {
    if (parent == nullptr) return;

    if (isLeft) {
        if (parent->getLeft() == nullptr)
            parent->setLeft(new Node(value));
    } else {
        if (parent->getRight() == nullptr)
            parent->setRight(new Node(value));
    }
}

void Model::deleteRoot() {
    tree.deleteTree(getRoot());
    setRoot(nullptr);
}

bool Model::deleteNode(const float& parentValue, const bool isLeft, const float& value) const {
    if (!getRoot()) return false;

    Node* parent = findNode(parentValue);
    if (!parent) return false;

    Node* child = isLeft ? parent->getLeft() : parent->getRight();
    if (!child) return false;
    if (child->getValue() != value) return false;

    Node* replacement = nullptr;
    if (child->getLeft() && !child->getRight()) {
        replacement = child->getLeft();
    } else if (!child->getLeft() && child->getRight()) {
        replacement = child->getRight();
    }

    if (isLeft) {
        parent->setLeft(replacement);
    } else {
        parent->setRight(replacement);
    }

    delete child;
    return true;
}

Node* Model::findNode(const float& value) const {
    return findNodeRecursive(getRoot(), value);
}

Node* Model::findNodeRecursive(Node* node, const float& value) {
    if (!node) return nullptr;
    if (node->getValue() == value) return node;
    if (Node* left = findNodeRecursive(node->getLeft(), value)) return left;
    return findNodeRecursive(node->getRight(), value);
}

std::string Model::getInfo() const {
    std::string info = "InOrder: " + inOrderTraversal() + "\n";
    info += "PreOrder: " + preOrderTraversal() + "\n";
    info += "PostOrder: " + postOrderTraversal() + "\n";
    info += "Level: " + levelOrderTraversal() + "\n";
    info += "AVL: " + std::string(isAVL() ? "Yes" : "No");
    return info;
}

std::string Model::preOrderTraversal() const {
    return tree.preOrder();
}

std::string Model::inOrderTraversal() const {
    return tree.inOrder();
}

std::string Model::postOrderTraversal() const {
    return tree.postOrder();
}

std::string Model::levelOrderTraversal() const {
    return tree.levelOrder();
}

bool Model::isAVL() const {
    return tree.isAVL();
}

bool Model::isBST() const {
    return tree.isBST(getRoot(), nullptr, nullptr);
}

Node* Model::balance(Node* root) {
    Node* newRoot = tree.balance(root);
    tree.setRoot(newRoot);
    return newRoot;
}

bool Model::isValidInsertion(const Node* parent, const bool isLeft, const float& value) const {
    if (!parent) return false;

    if (isLeft && value >= parent->getValue()) return false;
    if (!isLeft && value <= parent->getValue()) return false;

    Node* current = getRoot();
    while (current && current != parent) {
        if (value < current->getValue()) {
            if (parent->getValue() >= current->getValue()) return false;
            current = current->getLeft();
        } else {
            if (parent->getValue() <= current->getValue()) return false;
            current = current->getRight();
        }
    }
    return true;
}




