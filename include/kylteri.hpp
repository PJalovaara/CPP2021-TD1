#ifndef TD_KYLTERI
#define TD_KYLTERI

#include "enemy.hpp"

class Kylteri : public Enemy {
    Q_OBJECT
public:
    Kylteri(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent = 0);

private:
};


#endif