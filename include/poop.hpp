#ifndef INCLUDE_POOP_HPP_
#define INCLUDE_POOP_HPP_

#include "bullet.hpp"

/**
 * @brief A Poop is a Bullet that slows down enemies
 * 
 */
class Poop : public Bullet {
 public:
    explicit Poop(QGraphicsItem* parent = 0);
};

#endif  // INCLUDE_POOP_HPP_
