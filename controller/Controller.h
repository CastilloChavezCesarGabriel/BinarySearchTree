#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../model/Model.h"
#include "../view/View.h"
#include "DrawController.h"

class Controller final : public QObject {
    Q_OBJECT
private:
    Model* model;
    View* view;
    DrawController layout;
    bool isLeft{};

    void onUpdateTree(Node* root);
    bool isValidInput(const QString& text, float& value) const;

public:
    Controller(Model* model, View* view, QObject* parent = nullptr);

private slots:
    void handleInsertRoot(const QString &stringValue);
    void handleInsertNode(const QString &stringParent, const QString &stringValue);
    void handleRemoveRoot();
    void handleRemoveNode(const QString& stringParent, const QString& stringValue);
    void handleBalanceTree();
    void handleClearTree() const;
    void handleShowInfo() const;
    void handleExport() const;
};

#endif //CONTROLLER_H
