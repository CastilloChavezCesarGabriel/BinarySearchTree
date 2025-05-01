#include "Controller.h"

Controller::Controller(Model* model, View* view, QObject* parent)
    : QObject(parent), model(model), view(view) {

    connect(view->getCreateRootButton(), &QPushButton::clicked, this, &Controller::handleCreateRoot);
    connect(view->getCreateNodeButton(), &QPushButton::clicked, this, &Controller::handleCreateNode);
    connect(view->getDeleteRootButton(), &QPushButton::clicked, this, &Controller::handleDeleteRoot);
    connect(view->getDeleteNodeButton(), &QPushButton::clicked, this, &Controller::handleDeleteNode);
    connect(view->getInfoButton(), &QPushButton::clicked, this, &Controller::handleShowInfo);
    connect(view->getBalanceButton(), &QPushButton::clicked, this, &Controller::handleBalanceTree);
}

void Controller::handleCreateRoot() {
    const QString stringValue = view->getRootValue();

    if (stringValue.isEmpty()) {
        view->showUserFeedback("Please enter a valid input!", false);
        return;
    }

    bool ok;
    float value = stringValue.toFloat(&ok);
    if (!ok) {
        view->showUserFeedback("Invalid number format!", false);
        return;
    }

    if (model->isNodeExist(value)) {
        view->showUserFeedback("Root already exists!",false);
        return;
    }

    model->createRoot(value);
    updateTree(model->getRoot());
}

void Controller::handleCreateNode() {
    const QString stringParentValue = view->getParentValue()->text();
    const QString side = view->getSideValue()->currentText();
    const QString stringValue = view->getValue()->text();

    if (stringParentValue.isEmpty() || stringValue.isEmpty()) {
        view->showUserFeedback("Please fill all fields correctly!",false);
        return;
    }

    bool ok1, ok2;
    float parentValue = stringParentValue.toFloat(&ok1);
    float value = stringValue.toFloat(&ok2);
    if (!ok1 || !ok2) {
        view->showUserFeedback("Invalid float input!", false);
        return;
    }

    Node* parent = model->findNode(parentValue);
    if (!parent) {
        view->showUserFeedback("Parent node not found!",false);
        return;
    }

    const bool isLeft = side == "left";
    if (model->isNodeExist(value)) {
        view->showUserFeedback("Node with this value already exists!",false);
        return;
    }

    if (!model->isValidInsertion(parent, isLeft, value)) {
        view->showUserFeedback("BST violation: Invalid position for new node!", false);
        return;
    }

    if (!model->isBST()) {
        view->showUserFeedback("BST validation failed after insertion!", false);
        return;
    }

    model->createNode(parent, isLeft, value);
    updateTree(model->getRoot());
}

void Controller::handleDeleteRoot() {
    if (!model->getRoot()) {
        view->showUserFeedback("No root exists to delete!", false);
        return;
    }

    if (view->showConfirmation("Are you sure you want to delete this root? "
                               "The whole tree will be deleted!", "Delete Root")) {
        model->deleteRoot();
        updateTree(model->getRoot());
        view->showUserFeedback("Root node deleted successfully!", true);
    }
}

void Controller::handleDeleteNode() {
    const QString stringParent = view->getParentValue()->text();
    const bool isLeft = view->getSideValue()->currentText().toLower() == "left";
    const QString stringValue = view->getValue()->text();

    bool ok1, ok2;
    float parentValue = stringParent.toFloat(&ok1);
    float value = stringValue.toFloat(&ok2);
    if (!ok1 || !ok2) {
        view->showUserFeedback("Invalid float input for deletion!", false);
        return;
    }

    if (view->showConfirmation("Are you sure you want to delete this node?", "Delete Node")) {
        if (!model->deleteNode(parentValue, isLeft, value)) {
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

    if (model->isAVL()) {
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

int Controller::countLeaves(Node* node) {
    if (!node) return 0;
    if (!node->getLeft() && !node->getRight()) return 1;

    return countLeaves(node->getLeft()) + countLeaves(node->getRight());
}

void Controller::drawSubtree(Node* child, const DrawController& node) {
    if (!child) return;

    constexpr int baseOffset = 50;
    constexpr int verticalSpacing = 75;

    int leaves = countLeaves(child);
    int childX = node.getChildX(baseOffset, leaves);
    int childY = node.getChildY(verticalSpacing);

    view->drawLine(node.getParentX(), node.getParentY(), childX, childY, QColor(165, 42, 42));
    drawTree(child, childX, childY, node.getHorizontalOffSet() / 2);
}

void Controller::drawTree(Node* node, const int x, const int y, const int horizontalOffset) {
    if (!node) return;

    constexpr int radius = 20;
    view->drawCircle(x, y, radius,Qt::darkGreen);
    view->drawText(x - 10, y - 10, QString::number(node->getValue()));

    if (node->getLeft()) {
        DrawController left(x, y, horizontalOffset, -1);
        drawSubtree(node->getLeft(), left);
    }

    if (node->getRight()) {
        DrawController right(x, y, horizontalOffset, 1);
        drawSubtree(node->getRight(), right);
    }
}

