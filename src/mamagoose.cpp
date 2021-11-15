#include "mamagoose.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include <QTimer>
#include <QList>

MamaGoose::MamaGoose(QGraphicsScene* scene, QGraphicsItem* parent) : Tower(scene, parent) {
    // Set the graphics
    QPixmap p = QPixmap(":/images/MamaGoose.png");
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    setPixmap(p); // Set size for the goose
    UpdateAttackRadius(80); // MamaGoose has a larger radius
    attack_speed_ = 3;

    // CONNECT TIMER TO ATTACK_TARGET
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(AcquireTarget()));
    timer->start(1000 / attack_speed_);
};

void MamaGoose::AttackTarget(){
    Bullet* bullet = new Bullet();
    QPointF bullet_center = mapToScene(tower_center_); // Center the bullet position w.r.t the goose
    bullet->setPos(bullet_center.x(), bullet_center.y());

    QLineF ln(QPointF(x(), y()), attack_dest_);
    int angle = -ln.angle(); // ln.angle() is the angle of the ln counterclockwise,  NOTE: rotation will rotate clockwise
    bullet->setRotation(angle); // Rotate the bullet
    scene_->addItem(bullet); // Add the bullet into the scene
}

void MamaGoose::AcquireTarget() {
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = attack_area_->collidingItems();

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