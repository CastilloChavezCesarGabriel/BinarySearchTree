#include "Controller.h"

Controller::Controller(BinaryTreeModel* model, View* view, QObject* parent)
    : QObject(parent), model(model), view(view) {

    connect(view->getCreateRootButton(), &QPushButton::clicked, this, &Controller::handleCreateRoot);
    connect(view->getCreateNodeButton(), &QPushButton::clicked, this, &Controller::handleCreateNode);
    connect(view->getDeleteRootButton(), &QPushButton::clicked, this, &Controller::handleDeleteRoot);
    connect(view->getDeleteNodeButton(), &QPushButton::clicked, this, &Controller::handleDeleteNode);
    connect(view->getInfoButton(), &QPushButton::clicked, this, &Controller::handleShowInfo);
    connect(view->getBalanceButton(), &QPushButton::clicked, this, &Controller::handleBalanceTree);
}

void Controller::handleCreateRoot() {
    const QString value = view->getRootValue();

    if (value.isEmpty()) {
        view->showUserFeedback("Please enter a valid input!", false);
        return;
    }

    model->createRoot(value.toStdString());
    updateTree(model->getRoot());
}

void Controller::handleCreateNode() {
    const QString parentValue = view->getParentValue()->text();
    const QString side = view->getSideValue()->currentText();
    const QString value = view->getValue()->text();

    if (parentValue.isEmpty() || value.isEmpty()) {
        view->showUserFeedback("Please fill all fields correctly!",false);
        return;
    }

    Node* parent = model->findNode(parentValue.toStdString());
    if (!parent) {
        view->showUserFeedback("Parent node not found!",false);
        return;
    }

    const bool isLeft = side == "left";
    if (model->isNodeExist(value.toStdString())) {
        view->showUserFeedback("Node with this value already exists!",false);
        return;
    }

    if (!model->isValidInsertion(parent, isLeft, value.toStdString())) {
        view->showUserFeedback("BST violation: Invalid position for new node!", false);
        return;
    }

    if (!model->isBST(model->getRoot())) {
        view->showUserFeedback("BST validation failed after insertion!", false);
        return;
    }

    model->createNode(parent, isLeft, value.toStdString());
    updateTree(model->getRoot());
}

void Controller::handleDeleteRoot() {
    if (view->showConfirmation("Are you sure you want to delete this root?", "Delete Root")) {
        model->deleteRoot();
        updateTree(model->getRoot());
        view->showUserFeedback("Root node deleted successfully!", true);
    }
}

void Controller::handleDeleteNode() {
    const QString parent = view->getParentValue()->text();
    const bool isLeft = view->getSideValue()->currentText().toLower() == "left";
    const QString value = view->getValue()->text();

    if (view->showConfirmation("Are you sure you want to delete this node?", "Delete Node")) {
        if (!model->deleteNode(parent.toStdString(), isLeft, value.toStdString())) {
            view->showUserFeedback("Could not delete node. Check parent, side, and node value.",false);
        } else {
            updateTree(model->getRoot());
            view->showUserFeedback("Node deleted successfully!", true);
        }
    }
}

void Controller::handleBalanceTree() {
    if (!model->getRoot()) {
        view->showUserFeedback("Tree is empty, cannot balance!", false);
        return;
    }

    if (model->isAVLTree()) {
        view->showUserFeedback("The tree is already balanced.", true);
        return;
    }

    Node* newRoot = model->balance(model->getRoot());
    model->setRoot(newRoot);
    updateTree(newRoot);
    view->showUserFeedback("Tree balanced successfully!", true);
}

void Controller::handleShowInfo() const {
    const QString info = QString::fromStdString(model->getInfo());
    view->showMessage(info);
}

void Controller::updateTree(Node* root) {
    view->clearScene();
    drawTree(root, 400, 50, 100);
}

void Controller::drawTree(Node* node, const int x, const int y, const int horizontalOffset) {
    if (!node) return;

    constexpr int radius = 20;
    view->drawCircle(x, y, radius,Qt::darkGreen);
    view->drawText(x - 10, y - 10, QString::fromStdString(node->getValue()));

    if (node->getLeft()) {
        const int childX = x - horizontalOffset * 0.8;
        const int childY = y + 75;
        view->drawLine(x, y, childX, childY,QColor(165, 42, 42));
        drawTree(node->getLeft(), childX, childY, horizontalOffset / 2);
    }

    if (node->getRight()) {
        const int childX = x + horizontalOffset * 0.8;
        const int childY = y + 75;
        view->drawLine(x, y, childX, childY,QColor(165, 42, 42));
        drawTree(node->getRight(), childX, childY, horizontalOffset / 2);
    }
}

