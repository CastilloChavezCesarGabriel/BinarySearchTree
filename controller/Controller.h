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
    void handleAddRoot();
    void handleAddNode();
    void handleRemoveRoot();
    void handleRemoveNode();
    void handleBalanceTree();
    void handleShowInfo() const;
    void handleExport() const;
};

#endif //CONTROLLER_H
