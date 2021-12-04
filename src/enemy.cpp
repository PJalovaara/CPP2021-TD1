#include <enemy.hpp>

#include <QPixmap>
#include <QTimer>
#include <QString>
#include <qmath.h>

#include <QDebug>

#include <bullet.hpp>

Enemy::Enemy(Game* game, QGraphicsItem* parent) {
    game_ = game;
};
    
void Enemy::RotateToFacePoint(QPointF p) {
    QLineF ln(pos(), p);
    // Note that ln.angle() will return the the angle in counterclockwise direction but setRotation is clockwise
    setRotation(-ln.angle()); //-ln.angle()
};


void Enemy::MoveForward() {
    // If close to dest, rotate towards the next dest
    QLineF ln(pos(), dest_);

    // Getting hit by a bullet destroys the enemy
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = this->collidingItems();

    for(auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Bullet* bullet = dynamic_cast<Bullet*>(item);
        if(bullet) { // If cast is successful
            enemy_hp_ -= bullet->GetDamage();
            delete bullet;
            if(enemy_hp_ <= 0){ // If enemy dies
                Death();
                delete this;
                return;
            }
        }
    }

    // If enemy reaches final destination, the player loses hp and the memory is freed
    if(ln.length() < 30 && point_index_ >= path_points_.length() - 1) {
        ReachDest();
    }

    // Rotate to face the next point
    if(ln.length() < 10 && point_index_ < path_points_.length() - 1){ // Check the size of the radius
        point_index_++;
        dest_ = path_points_[point_index_];
        RotateToFacePoint(dest_);
    }
    
    // Move enemy forwards with its current angle
    double theta = rotation(); // return the angle in degrees
    double dy = speed_ * qSin(qDegreesToRadians(theta));
    double dx = speed_ * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
};

void Enemy::Death() {
    game_->SetMoney(game_->GetMoney() + price_);
    game_->UpdateMoneyText();
    game_->PlayEnemyDiesSfx();
};

void Enemy::ReachDest() {
    QProgressBar* health_bar = game_->GetHealthBar();
    int current_health = health_bar->value();
    if(current_health - damage_ >= 0) {
        health_bar->setValue(current_health - damage_);
        health_bar->setFormat(" HP: " + QString::number(current_health - damage_));
    } else {
        health_bar->setValue(0);
        health_bar->setFormat(" HP: " + QString::number(0));
    }
    delete this;
    return;
};

QPointF Enemy::GetDest() {
    return dest_;
};


