#ifndef INCLUDE_BASICGOOSE_HPP_
#define INCLUDE_BASICGOOSE_HPP_

#include "tower.hpp"

class BasicGoose : public Tower {
    Q_OBJECT

 public:
    explicit BasicGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
 public slots:
    void AcquireTarget();
};



#endif  // INCLUDE_BASICGOOSE_HPP_
