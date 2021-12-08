#ifndef INCLUDE_POOPERGOOSE_HPP_
#define INCLUDE_POOPERGOOSE_HPP_

#include "tower.hpp"

class PooperGoose : public Tower {
    Q_OBJECT

 public:
    explicit PooperGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
 public slots:
    void AcquireTarget();
};


#endif  // INCLUDE_POOPERGOOSE_HPP_
