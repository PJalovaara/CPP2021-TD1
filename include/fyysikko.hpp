#ifndef TD_FYYSIKKO
#define TD_FYYSIKKO

#include "enemy.hpp"

class Fyysikko : public Enemy {
    Q_OBJECT
public:
    Fyysikko(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
private:
};



#endif