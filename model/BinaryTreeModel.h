#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "Node.h"
#include <vector>

class BinaryTreeModel {
public:
    BinaryTreeModel();
    ~BinaryTreeModel();

    void createRoot(const float& value);
    static void createNode(Node* parent, bool isLeft, const float& value);
    void deleteRoot();
    bool deleteNode(const float& parentValue, bool isLeft, const float& value) const;
    Node* findNode(const float& value) const;
    std::string getInfo() const;
    static Node* findNodeRecursive(Node* node, const float& value);

    bool isAVL() const;
    static bool isBST(Node* node, Node* minNode = nullptr, Node* maxNode = nullptr);
    bool isValidInsertion(const Node* parent, bool isLeft, const float& value) const;
    bool isNodeExist(const float& value) const;

    std::string preOrderTraversal() const;
    std::string inOrderTraversal() const;
    std::string postOrderTraversal() const;

    static Node* balance(Node* root);
    Node* getRoot() const;
    void setRoot(Node* newRoot);

private:
    Node* root;

    static void deleteTree(Node* node);
    static int height(Node* node);
    static bool isBalanced(Node* node);
    static bool checkAVL(Node* node);
    static Node* leftRotate(Node* root);
    static Node* rightRotate(Node* root);
    static Node* leftRightRotate(Node* root);
    static Node* rightLeftRotate(Node* root);
};

#endif //BINARYTREE_H
