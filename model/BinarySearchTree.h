#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "Node.h"
#include <string>

class BinarySearchTree {
private:
    Node* root;

public:
    BinarySearchTree();
    ~BinarySearchTree();

    Node* getRoot() const;
    void setRoot(Node* newRoot);

    bool isAVL() const;
    static bool isBST(Node* node = nullptr, Node* minNode = nullptr, Node* maxNode = nullptr);

    std::string preOrder() const;
    std::string inOrder() const;
    std::string postOrder() const;
    std::string levelOrder() const;

    static Node* balance(Node* root);
    static void deleteTree(Node* node);

private:
    static int getHeight(Node* node);
    static bool checkAVL(Node* node);
    static bool isBalanced(Node* node);
    static Node* leftRotate(Node* root);
    static Node* rightRotate(Node* root);
    static Node* leftRightRotate(Node* root);
    static Node* rightLeftRotate(Node* root);
    static std::string formatFloat(float value);
};

#endif //BINARY_TREE_H
