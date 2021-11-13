#include "tower.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QList>

Tower::Tower(QGraphicsScene* scene, QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent) {
    scene_ = scene;
    // Set the graphics
    QPixmap p = QPixmap(":/images/SniperGoose.png");
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    setPixmap(p); // Set size for the goose


    // Set attack_radius and tower width and height
    attack_radius_ = 50;
    tower_width_ = p.width();
    tower_height_ = p.height();

    // Add more points to make it more round
    points_ = {QPointF(1,0), QPointF(2,0), QPointF(3,1), QPointF(3,2), QPoint(2,3), QPoint(1,3), QPoint(0,2), QPoint(0,1)};

    for(unsigned int i = 0; i < points_.size(); i++){
        points_[i] *= attack_radius_;
    }
    // Creating the QGraphicsPolygon, where This is the parent and now its added to the scene
    attack_area_ = new QGraphicsPolygonItem(points_, this);

    // CENTERING THE POLYGON (original center (1.5, 1.5))
    QPointF poly_center(1.5, 1.5);
    poly_center *= attack_radius_; // The scale factor for the 
    poly_center = mapToScene(poly_center);
    tower_center_ = QPointF(tower_width_ / 2, tower_height_ / 2); // Store the tower center coordinates
    QLineF ln(poly_center, tower_center_);
    attack_area_->setPos(x() + ln.dx(), y() + ln.dy()); // Moving the attack area along the line from poly_center to tower_center


    // CONNECT TIMER TO ATTACK_TARGET
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(AcquireTarget()));
    timer->start(1000);
}

unsigned int Tower::GetAttackRadius(){
    return attack_radius_;
}


void Tower::UpdateAttackRadius(unsigned int new_radius){
    // Points for the "unit" polygon
    points_ = {QPointF(1,0), QPointF(2,0), QPointF(3,1), QPointF(3,2), QPoint(2,3), QPoint(1,3), QPoint(0,2), QPoint(0,1)};
    for(unsigned int i = 0; i < points_.size(); i++){
        points_[i] *= new_radius;
    }
    if(attack_area_) {
        delete attack_area_; // Delete the old polygon
    }
    attack_area_ = new QGraphicsPolygonItem(points_, this);
    
    // Centering the polygon around the tower
    QPointF poly_center(1.5, 1.5);
    poly_center *= new_radius; // The scale factor for the polygon
    poly_center = mapToScene(poly_center);
    QLineF ln(poly_center, tower_center_);
    attack_area_->setPos(x() + ln.dx(), y() + ln.dy()); // Moving the attack area along the line from poly_center to tower_center

    attack_radius_ = new_radius; // Update the radius
}

void Tower::AttackTarget(){
    Bullet* bullet = new Bullet();
    QPointF bullet_center = mapToScene(tower_center_); // Center the bullet position w.r.t the goose
    bullet->setPos(bullet_center.x(), bullet_center.y());

    QLineF ln(QPointF(x(), y()), attack_dest_);
    int angle = -ln.angle(); // ln.angle() is the angle of the ln counterclockwise,  NOTE: rotation will rotate clockwise
    bullet->setRotation(angle); // Rotate the bullet
    scene_->addItem(bullet); // Add the bullet into the scene
}

double Tower::DistanceTo(QGraphicsItem* item) {
    QLineF ln(pos(), item->pos());
    return ln.length();
};

void Tower::AcquireTarget() {
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = attack_area_->collidingItems();

    // // colliding_items will always contain the tower itself
    // if(colliding_items.size() == 1){ // this is false. TO DO: filter colliding_items w.r.t enemies/towers
    //     has_target_ = false;
    //     return;
    // }
    has_target_ = false; // Initialize to no target
    double closest_dist = 300;
    QPointF closest_point = QPointF(0,0);
    for(auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if(enemy) { // If cast is successful
            double this_dist = DistanceTo(enemy);
            if(this_dist < closest_dist) {
                closest_dist = this_dist;
                closest_point = item->pos();
                has_target_ = true;
            }
        }
    }
    if(!has_target_) {
        return;
    }
    attack_dest_ = closest_point;
    AttackTarget();
};

