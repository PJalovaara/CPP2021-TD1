#ifndef INCLUDE_GOLDENBULLET_HPP_
#define INCLUDE_GOLDENBULLET_HPP_

#include "bullet.hpp"

/**
 * @brief A GoldenBullet is a Bullet that slows is fast and has high damage
 * 
 */
class GoldenBullet : public Bullet {
 public:
    explicit GoldenBullet(QGraphicsItem* parent = 0);
};


#endif  // INCLUDE_GOLDENBULLET_HPP_
