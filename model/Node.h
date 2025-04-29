#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;
class Node {
private:
    float value;
    Node *left{};
    Node *right{};

public:
    explicit Node(float value);

    float getValue() const;
    Node *&getLeft();
    Node *&getRight();
    void setLeft(Node* node);
    void setRight(Node* node);
};

#endif //NODE_H
