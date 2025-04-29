#include "Node.h"

Node::Node(float value) : value(value) {}

float Node::getValue() const {
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