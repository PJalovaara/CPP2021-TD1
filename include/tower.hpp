#ifndef TD_TOWER
#define TD_TOWER

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>

class Tower : public QGraphicsPixmapItem {
public:
    Tower(QGraphicsItem* parent = 0);
    unsigned int GetAttackRadius();
    void UpdateAttackRadius(unsigned int new_radius);
private:
    QGraphicsPolygonItem* attack_area_;
    unsigned int attack_radius_ = 0;
};


#endif