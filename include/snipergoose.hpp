#ifndef INCLUDE_SNIPERGOOSE_HPP_
#define INCLUDE_SNIPERGOOSE_HPP_

#include "tower.hpp"

/**
 * @brief 
 * 
 */
class SniperGoose : public Tower {
    Q_OBJECT

 public:
    explicit SniperGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    virtual void AttackTarget();
 public slots:
    virtual void AcquireTarget();
};

#endif  // INCLUDE_SNIPERGOOSE_HPP_
