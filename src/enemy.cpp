#include <enemy.hpp>

#include <QPixmap>
#include <QTimer>
#include <QString>
#include <qmath.h>

#include <bullet.hpp>
#include <poop.hpp>

/**
 * @brief Construct a new Enemy:: Enemy object
 * 
 * @param game 
 * @param parent 
 */
Enemy::Enemy(Game* game, QGraphicsItem* parent) {
    game_ = game;

    // Connect a timer to the move forward
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(MoveForward()));

    // Call the MoveForward function every 20 ms (approx 50 fps)
    timer_->start(20);

    // Distance traveled initialized to zero
    distance_traveled_ = 0;
}

Enemy::~Enemy() {
    delete timer_;
}

double Enemy::GetSpeed() {
    return speed_;
}

void Enemy::RotateToFacePoint(QPointF p) {
    QLineF ln(pos(), p);
    // Note that ln.angle() will return the the angle in counterclockwise direction but setRotation is clockwise
    setRotation(-ln.angle());  // -ln.angle()
}

/**
 * @brief 
 * 
 */
void Enemy::CheckPoop() {
    QList<QGraphicsItem*> colliding_items = this->collidingItems();

    for (auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Poop* poop = dynamic_cast<Poop*>(item);
        if (poop && speed_ > 1) {  // If cast is successful
            speed_ -= 0.5;
            delete poop;
        }
    }
    return;
}

/**
 * @brief 
 * 
 * @return double 
 */
double Enemy::DistanceLeft() {
    double total_distance = 0;
    for (int i = 0; i < path_points_.length() - 1; i++) {
        double x_squared = (path_points_[i+1].x() - path_points_[i].x()) * (path_points_[i+1].x() - path_points_[i].x());
        double y_squared = (path_points_[i+1].y() - path_points_[i].y()) * (path_points_[i+1].y() - path_points_[i].y());
        total_distance +=  qSqrt(x_squared + y_squared);
    }
    return total_distance - distance_traveled_;
}

/**
 * @brief 
 * 
 */
void Enemy::MoveForward() {
    // If close to dest, rotate towards the next dest
    QLineF ln(pos(), dest_);

    // Getting hit by poop slows enemies down
    CheckPoop();

    // Getting hit by a bullet destroys the enemy
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = this->collidingItems();

    for (auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Bullet* bullet = dynamic_cast<Bullet*>(item);
        if (bullet) {  // If cast is successful
            enemy_hp_ -= bullet->GetDamage();
            delete bullet;
            if (enemy_hp_ <= 0) {  // If enemy dies
                Death();
                delete this;
                return;
            }
        }
    }

    // If enemy reaches final destination, the player loses hp and the memory is freed
    if (ln.length() < 30 && point_index_ >= path_points_.length() - 1) {
        ReachDest();
        return;
    }

    // Rotate to face the next point
    if (ln.length() < 10 && point_index_ < path_points_.length() - 1) {  // Check the size of the radius
        point_index_++;
        dest_ = path_points_[point_index_];
        RotateToFacePoint(dest_);
    }

    // Move enemy forwards with its current angle
    double theta = rotation();  // return the angle in degrees
    double dy = speed_ * qSin(qDegreesToRadians(theta));
    double dx = speed_ * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
    distance_traveled_ += qSqrt(dx*dx + dy*dy);
}

void Enemy::Death() {
    game_->SetMoney(game_->GetMoney() + price_);
    game_->UpdateMoneyText();
    game_->PlayEnemyDiesSfx();
}

/**
 * @brief 
 * 
 */
void Enemy::ReachDest() {
    QProgressBar* health_bar = game_->GetHealthBar();
    int current_health = health_bar->value();
    if (current_health - damage_ > 0) {
        // Play honk because the geese are scared
        game_->PlayHonkSfx();
        health_bar->setValue(current_health - damage_);
        health_bar->setFormat(" HP: " + QString::number(current_health - damage_));
    } else {
        game_->GameOver();
        health_bar->setValue(0);
        health_bar->setFormat(" HP: " + QString::number(0));
    }
    delete this;
}

QPointF Enemy::GetDest() {
    return dest_;
}
