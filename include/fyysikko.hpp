#ifndef INCLUDE_FYYSIKKO_HPP_
#define INCLUDE_FYYSIKKO_HPP_

#include "enemy.hpp"

/**
 * @brief Fyysikko is a smart enemy that chooses the optimized with the shortest length.
 * 
 */
class Fyysikko : public Enemy {
    Q_OBJECT

 public:
    Fyysikko(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
 private:
};



#endif  // INCLUDE_FYYSIKKO_HPP_
