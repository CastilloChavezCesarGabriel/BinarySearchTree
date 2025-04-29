#ifndef DRAWCONTROLLER_H
#define DRAWCONTROLLER_H

class DrawController {
private:
    int parentX;
    int parentY;
    int horizontalOffset;
    int direction;

public:
    DrawController(int x, int y, int offset, int direction);

    int getChildX(int baseOffset, int childLeaves) const;
    int getChildY(int verticalSpacing) const;
    int getParentX() const;
    int getParentY() const;
    int getHorizontalOffSet() const;
};



#endif //DRAWCONTROLLER_H
