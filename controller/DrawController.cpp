#include "DrawController.h"

void DrawController::onCreateLayout(Node* root, const int startX, const int spacing) {
    currentX = startX;
    onAssignCoordinates(root, 0, spacing);
}

void DrawController::onAssignCoordinates(Node* node, const int depth, const int spacing) {
    if (!node) return;
    onAssignCoordinates(node->getLeft(), depth + 1, spacing);
    horizontalPosition[node] = currentX++;
    verticalPosition[node] = depth * spacing;
    onAssignCoordinates(node->getRight(), depth + 1, spacing);
}

void DrawController::onDrawTree(View* view, Node* node) {
    if (!node) return;

    const int x = horizontalPosition[node] * 60;
    const int y = verticalPosition[node];

    view->drawCircle(x, y, 20, Qt::darkGreen);
    view->drawText(x - 10, y - 10, QString::number(node->getValue()));

    if (node->getLeft()) {
        const int leftX = horizontalPosition[node->getLeft()] * 60;
        const int leftY = verticalPosition[node->getLeft()];
        view->drawLine(x, y, leftX, leftY, QColor(165, 42, 42));
        onDrawTree(view, node->getLeft());
    }

    if (node->getRight()) {
        const int rightX = horizontalPosition[node->getRight()] * 60;
        const int rightY = verticalPosition[node->getRight()];
        view->drawLine(x, y, rightX, rightY, QColor(165, 42, 42));
        onDrawTree(view, node->getRight());
    }
}
