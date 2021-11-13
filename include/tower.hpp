#ifndef TD_TOWER
#define TD_TOWER

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QObject>
#include <QGraphicsScene>

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tower(QGraphicsScene* scene, QGraphicsItem* parent = 0);
    unsigned int GetAttackRadius();
    void UpdateAttackRadius(unsigned int new_radius);
    double DistanceTo(QGraphicsItem* item);
    void AttackTarget();
public slots:
    void AcquireTarget();
private:
    QGraphicsScene* scene_;
    QVector<QPointF> points_;
    QPointF tower_center_;
    int tower_width_;
    int tower_height_;
    QGraphicsPolygonItem* attack_area_;
    unsigned int attack_radius_;;
    QPointF attack_dest_;
    bool has_target_;
};


#endif