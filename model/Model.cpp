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

void Model::insertRoot(const float& value) {
    if (!getRoot()) {
       setRoot(new Node(value));
    }
}

void Model::insertNode(Node* parent, const bool isLeft, const float& value) const {
    if (parent == nullptr) return;

    if (isLeft) {
        if (parent->getLeft() == nullptr)
            parent->setLeft(new Node(value));
    } else {
        if (parent->getRight() == nullptr)
            parent->setRight(new Node(value));
    }
}

void Model::removeRoot() {
    Node* root = getRoot();
    if (!root) return;

    Node* replacement = nullptr;
    if (root->getLeft() && !root->getRight()) {
        replacement = root->getLeft();
    } else if (!root->getLeft() && root->getRight()) {
        replacement = root->getRight();
    } else if (root->getLeft() && root->getRight()) {
        replacement = replaceNode(root);
    }

    setRoot(replacement);
    delete root;
}

bool Model::removeNode(const float& parentValue, const bool isLeft, const float& value) const {
    if (!getRoot()) return false;

    Node* parent = findNode(parentValue);
    if (!parent) return false;

    Node* child = isLeft ? parent->getLeft() : parent->getRight();
    if (!child) return false;
    if (child->getValue() != value) return false;

    Node* replacement = replaceNode(child);

    if (isLeft) {
        parent->setLeft(replacement);
    } else {
        parent->setRight(replacement);
    }

    delete child;
    return true;
}

Node* Model::replaceNode(Node* node) const {
    if (!node) return nullptr;

    if (!node->getLeft() && !node->getRight()) {
        return nullptr;
    }

    if (!node->getLeft()) {
        return node->getRight();
    }
    if (!node->getRight()) {
        return node->getLeft();
    }

    Node* successorParent = node;
    Node* successor = node->getRight();

    while (successor->getLeft()) {
        successorParent = successor;
        successor = successor->getLeft();
    }

    if (successorParent != node) {
        successorParent->setLeft(successor->getRight());
        successor->setRight(node->getRight());
    }

    successor->setLeft(node->getLeft());
    return successor;
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
    std::string info = "InOrder: " + tree.inOrder() + "\n";
    info += "PreOrder: " + tree.preOrder() + "\n";
    info += "PostOrder: " + tree.postOrder() + "\n";
    info += "Level: " + tree.levelOrder() + "\n";
    info += "AVL: " + std::string(isAVL() ? "Yes" : "No");
    return info;
}

bool Model::isAVL() const {
    return tree.isAVL();
}

Node* Model::balance(Node* root) {
    Node* newRoot = tree.balance(root);
    setRoot(newRoot);
    return newRoot;
}

void Model::clearTree() {
    tree.removeTree(getRoot());
    setRoot(nullptr);
}

bool Model::isValidInsertion(const Node* parent, const bool isLeft, const float& value) const {
    if (!parent) return false;

    if (isLeft && value >= parent->getValue()) return false;
    if (!isLeft && value <= parent->getValue()) return false;

    const Node* current = getRoot();
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




