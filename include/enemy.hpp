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
    Enemy(Game* game, QGraphicsItem* parent = 0);
    ~Enemy();
    void RotateToFacePoint(QPointF p);
    QPointF GetDest();
    virtual QList<QPointF> ChoosePath(QList<QList<QPointF>> paths) = 0;
    void ReachDest();
    int GetSpeed();
    virtual void Death();
    virtual void CheckPoop();
    double DistanceLeft();
public slots:
    void MoveForward();

protected:
    QTimer* timer_;
    QList<QPointF> path_points_;
    QPointF dest_;
    QPointF enemy_center_;
    int damage_;
    int speed_;
    int point_index_;
    Game* game_;
    int price_;
    int enemy_hp_;
    double distance_traveled_;
    double distance_left_;
};

#endif