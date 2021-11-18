#ifndef TD_ENEMY
#define TD_ENEMY

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> // List << element 
#include <QPointF>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(QList<QPointF> pathPoints, QGraphicsItem* parent = 0);
    QPointF GetEnemyCenter();
    void RotateToFacePoint(QPointF p);
public slots:
    void MoveForward();
private:
    QList<QPointF> pathPoints_;
    QPointF dest_;
    QPointF enemyCenter_;
    int speed_;
    int pointIndex_;
};

#endif