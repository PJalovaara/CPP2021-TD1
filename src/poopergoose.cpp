#include "poopergoose.hpp"

#include <QTimer>
#include <QList>

#include "poop.hpp"
#include "enemy.hpp"
/**
 * @brief Construct a new Pooper Goose:: Pooper Goose object
 * 
 * @param scene 
 * @param parent 
 */
PooperGoose::PooperGoose(QGraphicsScene* scene, QGraphicsItem* parent) : Tower(scene, parent) {
    // Set the graphics
    QPixmap p = QPixmap(":/images/poopergoose.png");
    p = p.scaled(100, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the goose
    attack_speed_ = 1;  // Attack once a second

    // Set attack_radius and tower width, height and center
    tower_width_ = p.width();
    tower_height_ = p.height();

    setOffset(-tower_width_ / 2, -tower_height_ / 2);  // Centering

    // Set the attack area to nullptr and then create it with the UpdateAttackRadius function
    attack_area_ = nullptr;
    UpgradeAttackRadius(120);  // MamaGoose has attackRadius of 120

    // Connect timer to AcquireTarget
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(AcquireTarget()));
    timer->start(1000 / attack_speed_);
}

void PooperGoose::AttackTarget() {
    Poop* poop = new Poop(this);
    poop->SetMaxRange(attack_radius_);  // Set max range for the bullet to equal the range of the tower
    poop->setPos(pos());  // Center the bullet position w.r.t the goose

    QLineF ln(pos(), attack_dest_);
    int angle = -ln.angle();  // ln.angle() is the angle of the ln counterclockwise,  NOTE: rotation will rotate clockwise
    poop->setRotation(angle);  // Rotate the bullet
    scene_->addItem(poop);  // Add the bullet into the scene
}
/**
 * @brief 
 * 
 */
void PooperGoose::AcquireTarget() {
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
