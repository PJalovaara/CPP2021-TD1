#ifndef TD_ENEMY
#define TD_ENEMY

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> // List << element 
#include <QPointF>
#include <QProgressBar>

#include "game.hpp"

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent = 0);
    void RotateToFacePoint(QPointF p);
public slots:
    virtual void MoveForward();
protected:
    QList<QPointF> path_points_;
    QPointF dest_;
    QPointF enemy_center_;
    int damage_;
    int speed_;
    int point_index_;
    Game* game_;
};

#endif