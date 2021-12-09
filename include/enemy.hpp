#ifndef INCLUDE_ENEMY_HPP_
#define INCLUDE_ENEMY_HPP_

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>
#include <QProgressBar>

#include "game.hpp"


/**
 * @brief Enemy is an abstract class that all enemies inherit.
 * 
 * Chooses its path on the map according to the virtual ChoosePath method.
 * Has a virtual void function Death when enemy has reached its destination.
 * All enemies move with the public slot MoveForward().
 * 
 */
class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

 public:
    explicit Enemy(Game* game, QGraphicsItem* parent = 0);
    ~Enemy();
    void RotateToFacePoint(QPointF p);
    QPointF GetDest();
    virtual QList<QPointF> ChoosePath(QList<QList<QPointF>> paths) = 0;
    void ReachDest();
    double GetSpeed();
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
    double speed_;
    int point_index_;
    Game* game_;
    int price_;
    int enemy_hp_;
    double distance_traveled_;
    double distance_left_;
};

#endif  // INCLUDE_ENEMY_HPP_
