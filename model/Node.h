#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;
class Node {
private:
    std::string value;
    Node *left{};
    Node *right{};

public:
    explicit Node(std::string value);

    std::string getValue() const;
    Node *&getLeft();
    Node *&getRight();
    void setLeft(Node* node);
    void setRight(Node* node);
};

#endif //NODE_H
