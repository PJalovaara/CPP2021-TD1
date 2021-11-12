#ifndef TD_TOWER
#define TD_TOWER

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QObject>
#include "game.hpp"

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tower(Game* game, QGraphicsItem* parent = 0);
    unsigned int GetAttackRadius();
    void UpdateAttackRadius(unsigned int new_radius);

public slots:
    void AttackTarget();

private:
    Game* game_;
    QVector<QPointF> points_;
    QGraphicsPolygonItem* attack_area_;
    unsigned int attack_radius_ = 40;
    QPointF attack_dest_;
};


#endif