#include <enemy.hpp>

#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QDebug>

Enemy::Enemy(QGraphicsItem* parent) {
    // Set graphics
    QPixmap p = QPixmap(":/images/arrow.png");
    setPixmap(p.scaled(50, 100, Qt::KeepAspectRatio)); // Set size for the enemy

    // Set the points in the path and the index of the point list
    points_ << QPointF(200,200) << QPointF(400, 200);
    point_index_ = 0;

     // Set initial destination
    dest_ = points_[point_index_];
    RotateToFacePoint(dest_);

    // Connect a timer to the move forward
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MoveForward()));

    // Call the MoveForward function every 150 ms
    timer->start(150);
};
    
    
void Enemy::RotateToFacePoint(QPointF p) {
    QLineF ln(pos(), p);
    // Note that ln.angle() will return the the angle in counterclockwise direction but setRotation is clockwise
    setRotation(-ln.angle()); 
};


void Enemy::MoveForward() {
    // If close to dest, rotate towards the next dest
    QLineF ln(pos(), dest_);
    if(ln.length() < 10 && point_index_ < points_.length() - 1){ // Check the size of the radius
        point_index_++;
        dest_ = points_[point_index_];
        RotateToFacePoint(dest_);
    }
    
    // Move enemy forwards with its current angle
    int STEPSIZE = 20;
    double theta = rotation(); // return the angle in degrees
    double dy = STEPSIZE * qSin(qDegreesToRadians(theta));
    double dx = STEPSIZE * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
};