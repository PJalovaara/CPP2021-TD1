#ifndef TD_TOWER
#define TD_TOWER

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QVector>
#include <QPointF>
#include <QPolygonF>

class Tower : public QGraphicsPixmapItem {
public:
    Tower(QGraphicsItem* parent = 0);
    unsigned int GetAttackRadius();
    void UpdateAttackRadius(unsigned int new_radius);
private:
    QVector<QPointF> points_;
    QGraphicsPolygonItem* attack_area_;
    unsigned int attack_radius_ = 40;
};


#endif