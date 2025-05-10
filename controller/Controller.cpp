#include "Controller.h"
#include <QFileDialog>

Controller::Controller(Model* model, View* view, QObject* parent)
    : QObject(parent), model(model), view(view) {
    connect(view, &View::onAddRootRequested, this, &Controller::handleInsertRoot);
    connect(view, &View::onAddNodeRequested, this, &Controller::handleInsertNode);
    connect(view, &View::onRemoveRootRequested, this, &Controller::handleRemoveRoot);
    connect(view, &View::onRemoveNodeRequested, this, &Controller::handleRemoveNode);
    connect(view, &View::onInfoRequested, this, &Controller::handleShowInfo);
    connect(view, &View::onBalanceRequested, this, &Controller::handleBalanceTree);
    connect(view, &View::onRemoveTreeRequested, this, &Controller::handleClearTree);
    connect(view, &View::onExportRequested, this, &Controller::handleExport);
}

void Controller::handleInsertRoot(const QString &stringValue) {
    if (stringValue.isEmpty()) {
        view->showUserFeedback("Please enter a valid input!", false);
        return;
    }

    float value;
    if (!view->isValidInput(stringValue, value)) {
        view->showUserFeedback("Invalid input!", false);
        return;
    }

    if (model->isNodeExist(value) || model->getRoot() && model->getRoot()->getValue() != value) {
        view->showUserFeedback("A root node already exists!", false);
        return;
    }

    model->insertRoot(value);
    onUpdateTree(model->getRoot());
}

void Controller::handleInsertNode(const QString &stringParent, const QString &stringValue) {
    if (stringParent.isEmpty() || stringValue.isEmpty()) {
        view->showUserFeedback("Please fill all fields correctly!",false);
        return;
    }

    float parentValue, value;
    if (!view->isValidInput(stringParent,parentValue) || !view->isValidInput(stringValue,value)) {
        view->showUserFeedback("Invalid input!", false);
        return;
    }

    Node* parent = model->findNode(parentValue);
    if (!parent) {
        view->showUserFeedback("Parent node not found!",false);
        return;
    }

    const bool isLeft = value < parent->getValue();
    if (model->isNodeExist(value)) {
        view->showUserFeedback("Node already exists!",false);
        return;
    }

    if ((isLeft && parent->getLeft() != nullptr) || (!isLeft && parent->getRight() != nullptr)) {
        view->showUserFeedback("That position already has a value!", false);
        return;
    }

    if (!model->isValidInsertion(parent, isLeft, value)) {
        view->showUserFeedback("Invalid position for new node!", false);
        return;
    }

    model->insertNode(parent, isLeft, value);
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
        view->showUserFeedback("Root deleted successfully!", true);
    }
}

void Controller::handleRemoveNode(const QString& stringParent, const QString& stringValue) {
    float parentValue, value;
    if (!view->isValidInput(stringParent,parentValue) || !view->isValidInput(stringValue,value)) {
        view->showUserFeedback("Node is empty or doesn't exist!", false);
        return;
    }

    const Node* parent = model->findNode(parentValue);
    if (!parent) {
        view->showUserFeedback("Parent node not found!", false);
        return;
    }

    const bool isLeft = value < parent->getValue();

    if (view->showConfirmation("Are you sure you want to delete this node?", "Delete Node")) {
        if (!model->removeNode(parentValue, isLeft, value)) {
            view->showUserFeedback("Could not delete node. Check parent and node value.",false);
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
        view->showUserFeedback("Tree is already balanced.", true);
        return;
    }

    Node* newRoot = model->balance(model->getRoot());
    model->setRoot(newRoot);
    onUpdateTree(newRoot);
    view->showUserFeedback("Tree balanced successfully!", true);
}

void Controller::handleClearTree() const {
    if (!model->getRoot()) {
        view->showUserFeedback("Tree is empty, nothing to clear!", false);
        return;
    }

    if (view->showConfirmation("Are you sure you want to clear the tree?", "Clear Tree")) {
        model->clearTree();
        view->clearScene();
        view->showUserFeedback("Tree cleared successfully!", true);
    }
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

    const QString fileName = QFileDialog::getSaveFileName(view, "Save Tree", "", "PNG (*.png);;JPEG (*.jpg)");
    if (!fileName.isEmpty()) {
        image.save(fileName);
        view->showUserFeedback("Tree exported successfully!", true);
    }
}
