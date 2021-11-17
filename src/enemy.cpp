#include <enemy.hpp>

#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QDebug>

Enemy::Enemy(QList<QPointF> pathPoints, QGraphicsItem* parent) {
    // Set graphics
    QPixmap p = QPixmap(":/images/arrow.png");
    setPixmap(p.scaled(50, 100, Qt::KeepAspectRatio)); // Set size for the enemy

    // Set the points in the path and the index of the point list
    pathPoints_ = pathPoints;
    pointIndex_ = 0;

     // Set initial destination
    dest_ = pathPoints_[pointIndex_];
    RotateToFacePoint(dest_);
    enemyCenter_ = QPointF(p.width() / 2, p.height() / 2);
    speed_ = 10;

    // Connect a timer to the move forward
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MoveForward()));

    // Call the MoveForward function every 80 ms
    timer->start(80);
};
    
    
void Enemy::RotateToFacePoint(QPointF p) {
    QLineF ln(pos(), p);
    // Note that ln.angle() will return the the angle in counterclockwise direction but setRotation is clockwise
    setRotation(-ln.angle()); 
};


void Enemy::MoveForward() {
    // If close to dest, rotate towards the next dest
    // TO DO: If enemy reaches final destination, player loses HP
    QLineF ln(pos(), dest_);
    
    // Enemy reaches final destination and the memory is freed
    if(ln.length() < 50 && pointIndex_ >= pathPoints_.length() - 1) {
        delete this;
        return;
    }

    // Rotate to face the next point
    if(ln.length() < 10 && pointIndex_ < pathPoints_.length() - 1){ // Check the size of the radius
        pointIndex_++;
        dest_ = pathPoints_[pointIndex_];
        RotateToFacePoint(dest_);
    }
    
    // Move enemy forwards with its current angle
    double theta = rotation(); // return the angle in degrees
    double dy = speed_ * qSin(qDegreesToRadians(theta));
    double dx = speed_ * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
};


