#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "Node.h"
#include <vector>
#include <string>

class BinaryTreeModel {
public:
    BinaryTreeModel();
    ~BinaryTreeModel();

    static bool isBST(Node* node, Node* minNode = nullptr, Node* maxNode = nullptr);
    bool isValidInsertion(const Node* parent, const bool isLeft, const std::string& value) const;
    bool isNodeExist(const std::string& value) const;
    void createRoot(const std::string &value);
    static void createNode(Node* parent, bool isLeft, const std::string &value);
    void deleteRoot();
    bool deleteNode(const std::string& parentValue, bool isLeft, const std::string& value) const;
    Node* findNode(const std::string& value) const;
    std::string getInfo() const;
    static Node* findNodeRecursive(Node* node, const std::string& value);

    std::string preOrderTraversal() const;
    std::string inOrderTraversal() const;
    std::string postOrderTraversal() const;

    static Node* balance(Node* root);
    bool isAVLTree() const;
    Node* getRoot() const;
    void setRoot(Node* newRoot);

private:
    Node* root;

    static void deleteTree(Node* node);
    static void preOrder(Node* node, std::vector<std::string>& result);
    static void inOrder(Node* node, std::vector<std::string>& result);
    static void inOrder(Node* node, std::vector<Node*>& nodes);
    static void postOrder(Node* node, std::vector<std::string>& result);
    static int height(Node* node);
    static bool isBalanced(Node* node);
    static bool checkAVL(Node* node);
    static Node* leftRotate(Node* root);
    static Node* rightRotate(Node* root);
    static Node* leftRightRotate(Node* root);
    static Node* rightLeftRotate(Node* root);
};

#endif //BINARYTREE_H
