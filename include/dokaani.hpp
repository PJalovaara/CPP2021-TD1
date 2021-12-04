#ifndef TD_DOKAANI
#define TD_DOKAANI

#include "enemy.hpp"

class Dokaani : public Enemy {
    Q_OBJECT
public:
    Dokaani(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
    void MoveForward();
private:
};



#endif