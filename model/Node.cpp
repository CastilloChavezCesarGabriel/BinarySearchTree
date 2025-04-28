#include "Node.h"

Node::Node(std::string value) : value(std::move(value)) {}

std::string Node::getValue() const {
    return value;
}

Node *&Node::getLeft() {
    return left;
}

Node *&Node::getRight() {
    return right;
}

void Node::setLeft(Node* node) {
    left = node;
}

void Node::setRight(Node* node) {
    right = node;
}