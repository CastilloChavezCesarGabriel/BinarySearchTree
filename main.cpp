#include <QApplication>
#include "model/BinaryTreeModel.h"
#include "view/View.h"
#include "controller/Controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    BinaryTreeModel model;
    View view;
    Controller controller(&model, &view);
    view.show();
    return app.exec();
}