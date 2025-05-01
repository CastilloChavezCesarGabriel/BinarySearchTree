#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "BinarySearchTree.h"
#include <vector>

class Model {
public:
    Model();

    void createRoot(const float& value);
    static void createNode(Node* parent, bool isLeft, const float& value);
    void deleteRoot();
    bool deleteNode(const float& parentValue, bool isLeft, const float& value) const;
    Node* findNode(const float& value) const;

    bool isAVL() const;
    bool isBST() const;
    bool isValidInsertion(const Node* parent, bool isLeft, const float& value) const;
    bool isNodeExist(const float& value) const;

    Node* balance(Node* root);
    std::string preOrderTraversal() const;
    std::string inOrderTraversal() const;
    std::string postOrderTraversal() const;
    std::string levelOrderTraversal() const;

    Node* getRoot() const;
    void setRoot(Node* newRoot);
    std::string getInfo() const;

private:
    BinarySearchTree tree;
    static Node* findNodeRecursive(Node* node, const float& value);
};

#endif //BINARYTREE_H
