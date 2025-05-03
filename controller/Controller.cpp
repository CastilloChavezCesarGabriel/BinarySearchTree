#include "Controller.h"
#include "DrawController.h"

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

    float value;
    if (!view->isValidInput(stringValue, value,&error)) {
        view->showUserFeedback(error, false);
        return;
    }

    if (model->isNodeExist(value) || model->getRoot() && model->getRoot()->getValue() != value) {
        view->showUserFeedback("A root node already exists!", false);
        return;
    }

    model->createRoot(value);
    onUpdateTree(model->getRoot());
}

void Controller::handleCreateNode() {
    const QString stringParentValue = view->getParentValue()->text();
    const QString side = view->getSideValue()->currentText();
    const QString stringValue = view->getValue()->text();

    if (stringParentValue.isEmpty() || stringValue.isEmpty()) {
        view->showUserFeedback("Please fill all fields correctly!",false);
        return;
    }

    float parentValue, value;
    if (!view->isValidInput(stringParentValue,parentValue,&error) || !view->isValidInput(stringValue,value,&error)) {
        view->showUserFeedback(error, false);
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
    onUpdateTree(model->getRoot());
}

void Controller::handleDeleteRoot() {
    if (!model->getRoot()) {
        view->showUserFeedback("No root exists to delete!", false);
        return;
    }

    if (view->showConfirmation("Are you sure you want to delete this root? ", "Delete Root")) {
        model->deleteRoot();
        onUpdateTree(model->getRoot());
        view->showUserFeedback("Root node deleted successfully!", true);
    }
}

void Controller::handleDeleteNode() {
    const QString stringParent = view->getParentValue()->text();
    const bool isLeft = view->getSideValue()->currentText().toLower() == "left";
    const QString stringValue = view->getValue()->text();

    float parentValue, value;
    if (!view->isValidInput(stringParent,parentValue,&error) || !view->isValidInput(stringValue,value,&error)) {
        view->showUserFeedback("Node is empty or doesn't exist!", false);
        return;
    }

    if (view->showConfirmation("Are you sure you want to delete this node?", "Delete Node")) {
        if (!model->deleteNode(parentValue, isLeft, value)) {
            view->showUserFeedback("Could not delete node. Check parent, side, and node value.",false);
        } else {
            onUpdateTree(model->getRoot());
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
    onUpdateTree(newRoot);
    view->showUserFeedback("Tree balanced successfully!", true);
}

void Controller::handleShowInfo() const {
    const QString info = QString::fromStdString(model->getInfo());
    view->showMessage(info);
}

void Controller::onUpdateTree(Node* root) {
    view->clearScene();
    layout.onCreateLayout(root, 0, 75);
    layout.onDrawTree(view, root);
}
