#ifndef TD_KONETEEKKARI
#define TD_KONETEEKKARI

#include "enemy.hpp"

class Koneteekkari : public Enemy {
    Q_OBJECT
public:
    Koneteekkari(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent = 0);

private:
};



#endif