#include "Node.h"

Node::Node(const float value) : value(value) {}

float Node::getValue() const {
    return value;
}

Node *Node::getLeft() const {
    return left;
}

Node *Node::getRight() const {
    return right;
}

void Node::setLeft(Node* node) {
    left = node;
}

void Node::setRight(Node* node) {
    right = node;
}

void Node::setValue(const float value) {
    this->value = value;
}