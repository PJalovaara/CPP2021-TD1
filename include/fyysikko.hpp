#ifndef TD_FYYSIKKO
#define TD_FYYSIKKO

#include "enemy.hpp"

class Fyysikko : public Enemy {
    Q_OBJECT
public:
    Fyysikko(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent = 0);

private:
};



#endif