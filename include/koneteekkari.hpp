#ifndef INCLUDE_KONETEEKKARI_HPP_
#define INCLUDE_KONETEEKKARI_HPP_

#include "enemy.hpp"

/**
 * @brief Koneteekkari is the basic Enemy that chooses its path at random.
 * 
 */
class Koneteekkari : public Enemy {
    Q_OBJECT

 public:
    Koneteekkari(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent = 0);
    QList<QPointF> ChoosePath(QList<QList<QPointF>> paths);
};



#endif  // INCLUDE_KONETEEKKARI_HPP_
