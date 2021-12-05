#ifndef TD_CRUISESHIP
#define TD_CRUISESHIP

#include <QList>
#include <QPointF>
#include "game.hpp"
#include "enemy.hpp"

class Cruiseship : public Enemy {
    Q_OBJECT
public:
    Cruiseship(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
    void Death();
    void CheckPoop();
private:
};

#endif