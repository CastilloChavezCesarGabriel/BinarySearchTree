#include "DrawController.h"
#include <iostream>

DrawController::DrawController(int x, int y, int offset, int direction)
        : parentX(x), parentY(y), horizontalOffset(offset), direction(direction) {}

int DrawController::getChildX(int baseOffset, int childLeaves) const {
    int offset = baseOffset * childLeaves;
    return parentX + direction * std::max(offset, horizontalOffset / 2);
}

int DrawController::getChildY(int verticalSpacing) const {
    return parentY + verticalSpacing;
}

int DrawController::getParentX() const {
    return parentX;
}

int DrawController::getParentY() const {
    return parentY;
}

int DrawController::getHorizontalOffSet() const {
    return horizontalOffset;
}
