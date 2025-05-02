#ifndef DRAWCONTROLLER_H
#define DRAWCONTROLLER_H
#include "../model/Model.h"
#include "../view/View.h"
#include <unordered_map>

class DrawController {
public:
    void onCreateLayout(Node* root, int startX, int spacing);
    void onDrawTree(View* view, Node* node);

private:
    int currentX = 0;
    std::unordered_map<Node*, int> horizontalPosition;
    std::unordered_map<Node*, int> verticalPosition;

    void onAssignCoordinates(Node* node, int depth, int spacing);
};

#endif //DRAWCONTROLLER_H
