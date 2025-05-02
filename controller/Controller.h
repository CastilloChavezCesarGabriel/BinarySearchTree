#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "../model/Model.h"
#include "../view/View.h"
#include "DrawController.h"

class Controller final : public QObject {
    Q_OBJECT
private:
    Model* model;
    View* view;
    QString error;

    static int countLeaves(Node* node);
    void drawSubtree(Node* child, const DrawController& node);
    void drawTree(Node* node, int x, int y, int horizontalOffset);
    void updateTree(Node* root);

public:
    Controller(Model* model, View* view, QObject* parent = nullptr);

private slots:
    void handleCreateRoot();
    void handleCreateNode();
    void handleDeleteRoot();
    void handleDeleteNode();
    void handleBalanceTree();
    void handleShowInfo() const;
};

#endif //CONTROLLER_H
