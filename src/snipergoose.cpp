#include "snipergoose.hpp"

#include <QTimer>
#include <QList>
#include <qmath.h>

#include "mamagoose.hpp"
#include "goldenbullet.hpp"
#include "enemy.hpp"
/**
 * @brief Construct a SniperGoose object
 * 
 * @param scene the Scene where the Tower is rendered
 * @param parent optional QGraphicsItem parent
 */
SniperGoose::SniperGoose(QGraphicsScene* scene, QGraphicsItem* parent) : Tower(scene, parent) {
    // Set the graphics
    QPixmap p = QPixmap(":/images/snipergoose.png");
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the goose
    attack_speed_ = 1;  // And a slow attack speed

    // Set attack_radius and tower width, height and center
    tower_width_ = p.width();
    tower_height_ = p.height();

    setOffset(-tower_width_ / 2, -tower_height_ / 2);  // Centering

    attack_area_ = nullptr;
    UpgradeAttackRadius(300);  // SniperGoose has a very large radius

    // CONNECT TIMER TO ATTACK_TARGET
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(AcquireTarget()));
    timer->start(1000 / attack_speed_);
}

void SniperGoose::AttackTarget() {
    GoldenBullet* bullet = new GoldenBullet(this);
    bullet->SetMaxRange(attack_radius_);
    bullet->setPos(pos());  // Center the bullet position w.r.t the goose

    QLineF ln(pos(), attack_dest_);
    int angle = -ln.angle();  // ln.angle() is the angle of the ln counterclockwise,  NOTE: rotation will rotate clockwise
    bullet->setRotation(angle);  // Rotate the bullet
    scene_->addItem(bullet);  // Add the bullet into the scene
}

/**
 * @brief Targets the Enemy closest to its destination (highest priority)
 * 
 */
void SniperGoose::AcquireTarget() {
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = attack_area_->collidingItems();

    has_target_ = false;  // Initialize to no target
    double dist_to_end = 10000;
    QPointF closest_point = QPointF(0, 0);
    Enemy* closest_enemy = nullptr;

    for (auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy) {  // If cast is successful
            double this_dist = enemy->DistanceLeft();
            if (this_dist < dist_to_end) {
                dist_to_end = this_dist;
                closest_point = enemy->pos();
                closest_enemy = enemy;
                has_target_ = true;
            }
        }
    }
    if (!has_target_) {
        return;
    }

    attack_dest_ = closest_enemy->pos();

    AttackTarget();
}
