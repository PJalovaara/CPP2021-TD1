#ifndef INCLUDE_MAMAGOOSE_HPP_
#define INCLUDE_MAMAGOOSE_HPP_

#include "tower.hpp"

class MamaGoose : public Tower {
    Q_OBJECT

 public:
    explicit MamaGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
 public slots:
    void AcquireTarget();
};



#endif  // INCLUDE_MAMAGOOSE_HPP_
