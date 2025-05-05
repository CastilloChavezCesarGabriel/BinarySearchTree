#include "Controller.h"
#include "DrawController.h"
#include <QFileDialog>

Controller::Controller(Model* model, View* view, QObject* parent)
    : QObject(parent), model(model), view(view) {

    connect(view, &View::onAddRootRequested, this, &Controller::handleAddRoot);
    connect(view, &View::onAddNodeRequested, this, &Controller::handleAddNode);
    connect(view, &View::onRemoveRootButton, this, &Controller::handleRemoveRoot);
    connect(view, &View::onRemoveNodeButton, this, &Controller::handleRemoveNode);
    connect(view, &View::onInfoButton, this, &Controller::handleShowInfo);
    connect(view, &View::onBalanceButton, this, &Controller::handleBalanceTree);
    connect(view, &View::onExportButton, this, &Controller::handleExport);
}

void Controller::handleAddRoot(const QString &stringValue) {
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

    model->addRoot(value);
    onUpdateTree(model->getRoot());
}

void Controller::handleAddNode(const QString &stringParent, const QString &side, const QString &stringValue) {
    if (stringParent.isEmpty() || stringValue.isEmpty()) {
        view->showUserFeedback("Please fill all fields correctly!",false);
        return;
    }

    float parentValue, value;
    if (!view->isValidInput(stringParent,parentValue,&error) || !view->isValidInput(stringValue,value,&error)) {
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

    model->addNode(parent, isLeft, value);
    onUpdateTree(model->getRoot());
}

void Controller::handleRemoveRoot() {
    if (!model->getRoot()) {
        view->showUserFeedback("No root exists to delete!", false);
        return;
    }

    if (view->showConfirmation("Are you sure you want to delete this root? ", "Delete Root")) {
        model->removeRoot();
        onUpdateTree(model->getRoot());
        view->showUserFeedback("Root node deleted successfully!", true);
    }
}

void Controller::handleRemoveNode(const QString& stringParent, const QString& side, const QString& stringValue) {
    float parentValue, value;
    if (!view->isValidInput(stringParent,parentValue,&error) || !view->isValidInput(stringValue,value,&error)) {
        view->showUserFeedback("Node is empty or doesn't exist!", false);
        return;
    }

    const bool isLeft = side.toLower() == "left";

    if (view->showConfirmation("Are you sure you want to delete this node?", "Delete Node")) {
        if (!model->removeNode(parentValue, isLeft, value)) {
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

void Controller::handleExport() const {
    QImage image;
    view->render(image);

    if (image.isNull()) {
        view->showUserFeedback("No tree to export!", false);
        return;
    }

    const QString fileName = QFileDialog::getSaveFileName(view, "Save Tree Image", "", "PNG (*.png);;JPEG (*.jpg)");
    if (!fileName.isEmpty()) {
        image.save(fileName);
        view->showUserFeedback("Tree exported successfully!", true);
    }
}
