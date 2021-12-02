#ifndef TD_KONETEEKKARI
#define TD_KONETEEKKARI

#include "enemy.hpp"

class Koneteekkari : public Enemy {
    Q_OBJECT
public:
    Koneteekkari(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
private:
};



#endif