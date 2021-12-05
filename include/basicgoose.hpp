#ifndef TD_BASICGOOSE
#define TD_BASICGOOSE

#include "tower.hpp"

class BasicGoose : public Tower {
    Q_OBJECT
public:
    BasicGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
public slots:
    void AcquireTarget();
};



#endif