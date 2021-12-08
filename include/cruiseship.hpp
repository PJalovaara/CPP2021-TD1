#ifndef INCLUDE_CRUISESHIP_HPP_
#define INCLUDE_CRUISESHIP_HPP_

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
};

#endif  // INCLUDE_CRUISESHIP_HPP_
