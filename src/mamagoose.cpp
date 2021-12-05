#include "mamagoose.hpp"
<<<<<<< HEAD

=======
#include "plasmaball.hpp"
#include "enemy.hpp"
>>>>>>> ee0727990735f22f93acc96f1c2095dbf03761c9
#include <QTimer>
#include <QList>
#include <QDebug>

#include "bullet.hpp"
#include "enemy.hpp"

MamaGoose::MamaGoose(QGraphicsScene* scene, QGraphicsItem* parent) : Tower(scene, parent) {
    // Set the graphics
    QPixmap p = QPixmap(":/images/mamagoose.png");
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
<<<<<<< HEAD
    setPixmap(p);  // Set size for the goose
    attack_speed_ = 3;  // Attack 3 times a second
=======
    setPixmap(p); // Set size for the goose
    attack_speed_ = 10; // Attack 3 times a second
>>>>>>> ee0727990735f22f93acc96f1c2095dbf03761c9

    // Set attack_radius and tower width, height and center
    tower_width_ = p.width();
    tower_height_ = p.height();

    setOffset(-tower_width_ / 2, -tower_height_ / 2);  // Centering

    // Set the attack area to nullptr and then create it with the UpdateAttackRadius function
    attack_area_ = nullptr;
    UpgradeAttackRadius(120);  // MamaGoose has attackRadius of 120

    // Connect timer to AcquireTarget
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(AcquireTarget()));
    timer->start(1000 / attack_speed_);
}

<<<<<<< HEAD
void MamaGoose::AttackTarget() {
    Bullet* bullet = new Bullet(this);
    bullet->SetMaxRange(attack_radius_);  // Set max range for the bullet to equal the range of the tower
    bullet->setPos(pos());  // Center the bullet position w.r.t the goose
=======
void MamaGoose::AttackTarget(){
    PlasmaBall* bullet = new PlasmaBall(this);
    bullet->SetMaxRange(attack_radius_); // Set max range for the bullet to equal the range of the tower
    bullet->setPos(pos()); // Center the bullet position w.r.t the goose
>>>>>>> ee0727990735f22f93acc96f1c2095dbf03761c9

    QLineF ln(pos(), attack_dest_);
    int angle = -ln.angle();  // ln.angle() is the angle of the ln counterclockwise,  NOTE: rotation will rotate clockwise
    bullet->setRotation(angle);  // Rotate the bullet
    scene_->addItem(bullet);  // Add the bullet into the scene
}

void MamaGoose::AcquireTarget() {
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = attack_area_->collidingItems();

    has_target_ = false;  // Initialize to no target
    double closest_dist = 1000;
    QPointF closest_point = QPointF(0, 0);

    for (auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy) {  // If cast is successful
            double this_dist = DistanceTo(enemy);
            if (this_dist < closest_dist) {
                closest_dist = this_dist;
                closest_point = enemy->pos();
                has_target_ = true;
            }
        }
    }
    if (!has_target_) {
        return;
    }
    attack_dest_ = closest_point;
    AttackTarget();
}
