#ifndef INCLUDE_DOKAANI_HPP_
#define INCLUDE_DOKAANI_HPP_

#include "enemy.hpp"

/**
 * @brief Dokaani is the head of the enemies which takes a lot of damage but also has nice yield.
 * 
 */
class Dokaani : public Enemy {
    Q_OBJECT

 public:
    Dokaani(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
    void MoveForward();
    void Death();
};



#endif  // INCLUDE_DOKAANI_HPP_
