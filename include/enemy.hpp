#ifndef TD_ENEMY
#define TD_ENEMY

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> // List << element 
#include <QPointF>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = 0);
    void RotateToFacePoint(QPointF p);
public slots:
    void MoveForward();
private:
    QList<QPointF> points_;
    QPointF dest_;
    int point_index_;
};

#endif