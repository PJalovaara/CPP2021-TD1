#ifndef TD_POOPERGOOSE
#define TD_POOPERGOOSE

#include "tower.hpp"

class PooperGoose : public Tower {
    Q_OBJECT
public:
    PooperGoose(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void AttackTarget();
public slots:
    void AcquireTarget();
};


#endif