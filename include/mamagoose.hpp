#ifndef TD_MAMAGOOSE
#define TD_MAMAGOOSE

#include "tower.hpp"

class MamaGoose : public Tower {
    Q_OBJECT
public:
    MamaGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
public slots:
    void AcquireTarget();
};



#endif