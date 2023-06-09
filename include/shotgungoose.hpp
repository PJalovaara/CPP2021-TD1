#ifndef INCLUDE_SHOTGUNGOOSE_HPP_
#define INCLUDE_SHOTGUNGOOSE_HPP_

#include "tower.hpp"

/**
 * @brief A close-range Tower that shoots multiple Bullet objects
 * 
 */
class ShotgunGoose : public Tower {
    Q_OBJECT

 public:
    explicit ShotgunGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
 public slots:
    void AcquireTarget();
};



#endif  // INCLUDE_SHOTGUNGOOSE_HPP_
