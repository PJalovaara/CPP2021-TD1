#ifndef TD_SQUARE_TOWER
#define TD_SQUARE_TOWER

#include <QGraphicsRectItem>
#include <QGraphicsItem>

class SquareTower : public QGraphicsRectItem {
public:
    void keyPressEvent(QKeyEvent* event);
};


#endif