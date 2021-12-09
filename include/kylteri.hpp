#ifndef INCLUDE_KYLTERI_HPP_
#define INCLUDE_KYLTERI_HPP_

#include "enemy.hpp"

/**
 * @brief Kylteri is a quick enemy but always chooses the path with the closest Tower.
 * 
 */
class Kylteri : public Enemy {
    Q_OBJECT

 public:
    Kylteri(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
};


#endif  // INCLUDE_KYLTERI_HPP_
