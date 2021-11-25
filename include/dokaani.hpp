#ifndef TD_DOKAANI
#define TD_DOKAANI

#include "enemy.hpp"

class Dokaani : public Enemy {
    Q_OBJECT
public:
    Dokaani(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent = 0);

private:
};



#endif