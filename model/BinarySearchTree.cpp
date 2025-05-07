#include "BinarySearchTree.h"
#include "TreeTraversal.h"
#include <sstream>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    removeTree(root);
}

Node* BinarySearchTree::getRoot() const {
    return root;
}

void BinarySearchTree::setRoot(Node* newRoot) {
    root = newRoot;
}

int BinarySearchTree::getHeight(Node* node) {
    if (node == nullptr) return -1;
    return std::max(getHeight(node->getLeft()), getHeight(node->getRight())) + 1;
}

bool BinarySearchTree::isAVL() const {
    return isBST(root, nullptr, nullptr) && checkAVL(root);
}

bool BinarySearchTree::checkAVL(Node* node) {
    if (node == nullptr) return true;
    if (!isBalanced(node)) return false;
    return checkAVL(node->getLeft()) && checkAVL(node->getRight());
}

bool BinarySearchTree::isBST(Node* node, Node* minNode, Node* maxNode) {
    if (!node) return true;

    if (minNode && node->getValue() <= minNode->getValue())
        return false;
    if (maxNode && node->getValue() >= maxNode->getValue())
        return false;

    return isBST(node->getLeft(), minNode, node) &&
           isBST(node->getRight(), node, maxNode);
}

bool BinarySearchTree::isBalanced(Node* node) {
    const int balanceFactor = findBalanceFactor(node);
    return std::abs(balanceFactor) <= 1;
}

Node* BinarySearchTree::balance(Node* root) {
    if (root == nullptr) return nullptr;

    root->setLeft(balance(root->getLeft()));
    root->setRight(balance(root->getRight()));

    const int balanceFactor = findBalanceFactor(root);

    if (balanceFactor > 1) {
        if (findBalanceFactor(root->getLeft()) >= 0) {
            return rightRotate(root);
        }
        return leftRightRotate(root);
    }

    if (balanceFactor < -1) {
        if (findBalanceFactor(root->getRight()) <= 0) {
            return leftRotate(root);
        }
        return rightLeftRotate(root);
    }

    return root;
}

int BinarySearchTree::findBalanceFactor(Node *node) {
    if (!node) return 0;
    const int left = node->getLeft() ? getHeight(node->getLeft()) : -1;
    const int right = node->getRight() ? getHeight(node->getRight()) : -1;
    return left - right;
}

std::string BinarySearchTree::preOrder() const {
    std::vector<float> result;
    TreeTraversal::preOrder(root, result);
    std::string output;
    for (const float value : result) {
        output += formatFloat(value) + " ";
    }
    return output;
}

std::string BinarySearchTree::inOrder() const {
    std::vector<float> result;
    TreeTraversal::inOrder(root, result);
    std::string output;
    for (const float value : result) {
        output += formatFloat(value) + " ";
    }
    return output;
}

std::string BinarySearchTree::postOrder() const {
    std::vector<float> result;
    TreeTraversal::postOrder(root, result);
    std::string output;
    for (const float value : result) {
        output += formatFloat(value) + " ";
    }
    return output;
}

std::string BinarySearchTree::levelOrder() const {
    std::vector<float> result;
    TreeTraversal::levelOrder(root, result);
    std::string output;
    for (const float value : result) {
        output += formatFloat(value) + " ";
    }
    return output;
}

Node* BinarySearchTree::leftRotate(Node* root) {
    Node* newRoot = root->getRight();
    root->setRight(newRoot->getLeft());
    newRoot->setLeft(root);
    return newRoot;
}

Node* BinarySearchTree::rightRotate(Node* root) {
    Node* newRoot = root->getLeft();
    root->setLeft(newRoot->getRight());
    newRoot->setRight(root);
    return newRoot;
}

Node* BinarySearchTree::leftRightRotate(Node* root) {
    root->setLeft(leftRotate(root->getLeft()));
    return rightRotate(root);
}

Node* BinarySearchTree::rightLeftRotate(Node* root) {
    root->setRight(rightRotate(root->getRight()));
    return leftRotate(root);
}

void BinarySearchTree::removeTree(Node* node) {
    if (node == nullptr) return;
    removeTree(node->getLeft());
    removeTree(node->getRight());
    delete node;
}

std::string BinarySearchTree::formatFloat(const float value) {
    std::ostringstream oss;
    oss << std::defaultfloat << value;
    return oss.str();
}



