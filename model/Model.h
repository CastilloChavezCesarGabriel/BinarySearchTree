#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "BinarySearchTree.h"
#include <vector>

class Model {
private:
    BinarySearchTree tree;
    Node* replaceNode(Node* node) const;
    static Node* findNodeRecursive(Node* node, const float& value);

public:
    Model();

    Node* getRoot() const;
    void setRoot(Node* newRoot);

    void insertRoot(const float& value);
    void insertNode(Node* parent, bool isLeft, const float& value) const;
    void removeRoot();
    bool removeNode(const float& parentValue, bool isLeft, const float& value) const;
    Node* findNode(const float& value) const;
    void clearTree();

    bool isAVL() const;
    bool isValidInsertion(const Node* parent, bool isLeft, const float& value) const;
    bool isNodeExist(const float& value) const;
    bool isNodeOccupied(Node* parent, bool isLeft) const;
    bool isRootOccupied(float value) const;

    Node* balance(Node* root);
    std::string getInfo() const;
};

#endif //BINARYTREE_H
