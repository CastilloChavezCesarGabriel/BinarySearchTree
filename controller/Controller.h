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
    QString error;
    DrawController layout;

    void onUpdateTree(Node* root);

public:
    Controller(Model* model, View* view, QObject* parent = nullptr);

private slots:
    void handleAddRoot(const QString &stringValue);
    void handleAddNode(const QString &stringParent, const QString &side, const QString &stringValue);
    void handleRemoveRoot();
    void handleRemoveNode(const QString& stringParent, const QString& side, const QString& stringValue);
    void handleBalanceTree();
    void handleClearTree() const;
    void handleShowInfo() const;
    void handleExport() const;
};

#endif //CONTROLLER_H
