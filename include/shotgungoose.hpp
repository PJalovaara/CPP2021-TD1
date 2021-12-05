#ifndef TD_SHOTGUNGOOSE
#define TD_SHOTGUNGOOSE

#include "tower.hpp"

class ShotgunGoose : public Tower {
    Q_OBJECT
public:
    ShotgunGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
public slots:
    void AcquireTarget();
};



#endif