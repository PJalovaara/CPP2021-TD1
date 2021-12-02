#ifndef TD_KYLTERI
#define TD_KYLTERI

#include "enemy.hpp"

class Kylteri : public Enemy {
    Q_OBJECT
public:
    Kylteri(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);

private:
};


#endif