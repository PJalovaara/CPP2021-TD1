#ifndef TD_SNIPERGOOSE
#define TD_SNIPERGOOSE

#include "tower.hpp"

class SniperGoose : public Tower {
    Q_OBJECT
public:
    SniperGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    virtual void AttackTarget();
public slots:
    virtual void AcquireTarget();
};



#endif