#ifndef INCLUDE_BULLET_HPP_
#define INCLUDE_BULLET_HPP_

#include <QGraphicsPixmapItem>
#include <QObject>
/**
 * @brief 
 * 
 */
class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT  // Macro needed to work with signals and slots (and it needs to inherit from QObject)

 public:
    explicit Bullet(QGraphicsItem* parent = 0);
    double GetMaxRange();
    void SetMaxRange(double range);
    double GetDistanceTraveled();
    void SetDistanceTraveled(double dist);
    int GetDamage();
 public slots:
    void Move();

 protected:
    double speed_;
    double max_range_;
    double distance_traveled_;
    int bullet_damage_;
};




#endif  // INCLUDE_BULLET_HPP_
