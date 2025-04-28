#include "BinaryTreeModel.h"
#include <queue>
#include <cmath>

BinaryTreeModel::BinaryTreeModel() : root(nullptr) {}

BinaryTreeModel::~BinaryTreeModel() {
    deleteTree(root);
}

bool BinaryTreeModel::isNodeExist(const std::string& value) const {
    return findNode(value) != nullptr;
}

void BinaryTreeModel::createRoot(const std::string &value) {
    if (root == nullptr) {
        root = new Node(value);
    }
}

void BinaryTreeModel::createNode(Node* parent, const bool isLeft, const std::string &value) {
    if (parent == nullptr) return;

    if (isLeft) {
        parent->setLeft(new Node(value));
    } else {
        parent->setRight(new Node(value));
    }
}

void BinaryTreeModel::deleteRoot() {
    deleteTree(root);
    root = nullptr;
}

bool BinaryTreeModel::deleteNode(const std::string& parentValue, const bool isLeft, const std::string& value) const {
    if (!root) return false;

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

Node* BinaryTreeModel::findNode(const std::string& value) const {
    return findNodeRecursive(root, value);
}

Node* BinaryTreeModel::findNodeRecursive(Node* node, const std::string& value) {
    if (!node) return nullptr;
    if (node->getValue() == value) return node;
    if (Node* left = findNodeRecursive(node->getLeft(), value)) return left;
    return findNodeRecursive(node->getRight(), value);
}

std::string BinaryTreeModel::getInfo() const {
    std::string info = "InOrder: " + inOrderTraversal() + "\n";
    info += "PreOrder: " + preOrderTraversal() + "\n";
    info += "PostOrder: " + postOrderTraversal() + "\n";
    info += "Is AVL: " + std::string(isAVLTree() ? "Yes" : "No");
    return info;
}

std::string BinaryTreeModel::preOrderTraversal() const {
    std::vector<std::string> result;
    preOrder(root, result);
    std::string output;
    for (const std::string &value : result) {
        output += value + " ";
    }
    return output;
}

std::string BinaryTreeModel::inOrderTraversal() const {
    std::vector<std::string> result;
    inOrder(root, result);
    std::string output;
    for (std::string &value : result) {
        output += value + " ";
    }
    return output;
}

std::string BinaryTreeModel::postOrderTraversal() const {
    std::vector<std::string> result;
    postOrder(root, result);
    std::string output;
    for (const std::string &value : result) {
        output += value + " ";
    }
    return output;
}

bool BinaryTreeModel::isAVLTree() const {
    return checkAVL(root);
}

Node* BinaryTreeModel::getRoot() const {
    return root;
}

void BinaryTreeModel::setRoot(Node* newRoot) {
    root = newRoot;
}

void BinaryTreeModel::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->getLeft());
    deleteTree(node->getRight());
    delete node;
}

void BinaryTreeModel::preOrder(Node* node, std::vector<std::string>& result) {
    if (node == nullptr) return;
    result.push_back(node->getValue());
    preOrder(node->getLeft(), result);
    preOrder(node->getRight(), result);
}

void BinaryTreeModel::inOrder(Node* node, std::vector<std::string>& result) {
    if (node == nullptr) return;
    inOrder(node->getLeft(), result);
    result.push_back(node->getValue());
    inOrder(node->getRight(), result);
}

void BinaryTreeModel::inOrder(Node* node, std::vector<Node*>& nodes) {
    if (node == nullptr) return;
    inOrder(node->getLeft(), nodes);
    nodes.push_back(node);
    inOrder(node->getRight(), nodes);
}

void BinaryTreeModel::postOrder(Node* node, std::vector<std::string>& result) {
    if (node == nullptr) return;
    postOrder(node->getLeft(), result);
    postOrder(node->getRight(), result);
    result.push_back(node->getValue());
}

int BinaryTreeModel::height(Node* node) {
    if (node == nullptr) return 0;
    return std::max(height(node->getLeft()), height(node->getRight())) + 1;
}

bool BinaryTreeModel::isBalanced(Node* node) {
    const int leftHeight = height(node->getLeft());
    const int rightHeight = height(node->getRight());
    return std::abs(leftHeight - rightHeight) <= 1;
}

bool BinaryTreeModel::checkAVL(Node* node) {
    if (node == nullptr) return true;
    if (!isBalanced(node)) return false;
    return checkAVL(node->getLeft()) && checkAVL(node->getRight());
}

Node* BinaryTreeModel::leftRotate(Node* root) {
    Node* newRoot = root->getRight();
    root->setRight(newRoot->getLeft());
    newRoot->setLeft(root);
    return newRoot;
}

Node* BinaryTreeModel::rightRotate(Node* root) {
    Node* newRoot = root->getLeft();
    root->setLeft(newRoot->getRight());
    newRoot->setRight(root);
    return newRoot;
}

Node* BinaryTreeModel::leftRightRotate(Node* root) {
    root->setLeft(leftRotate(root->getLeft()));
    return rightRotate(root);
}

Node* BinaryTreeModel::rightLeftRotate(Node* root) {
    root->setRight(rightRotate(root->getRight()));
    return leftRotate(root);
}

Node* BinaryTreeModel::balance(Node* root) {
    if (root == nullptr) return nullptr;

    root->setLeft(balance(root->getLeft()));
    root->setRight(balance(root->getRight()));

    const int balanceFactor = height(root->getLeft()) - height(root->getRight());

    if (balanceFactor > 1) {
        if (height(root->getLeft()->getLeft()) >= height(root->getLeft()->getRight())) {
            return rightRotate(root);
        }
        return leftRightRotate(root);
    }

    if (balanceFactor < -1) {
        if (height(root->getRight()->getRight()) >= height(root->getRight()->getLeft())) {
            return leftRotate(root);
        }
        return rightLeftRotate(root);
    }

    return root;
}

bool BinaryTreeModel::isBST(Node* node, Node* minNode, Node* maxNode) {
    if (!node) return true;

    if (minNode && node->getValue() <= minNode->getValue())
        return false;
    if (maxNode && node->getValue() >= maxNode->getValue())
        return false;

    return isBST(node->getLeft(), minNode, node) &&
           isBST(node->getRight(), node, maxNode);
}

bool BinaryTreeModel::isValidInsertion(const Node* parent, const bool isLeft, const std::string& value) const {
    if (!parent) return false;

    if (isLeft && value >= parent->getValue()) return false;
    if (!isLeft && value <= parent->getValue()) return false;

    Node* current = root;
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


