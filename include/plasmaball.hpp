#ifndef INCLUDE_PLASMABALL_HPP_
#define INCLUDE_PLASMABALL_HPP_

#include "bullet.hpp"

/**
 * @brief A PlasmaBall is a Bullet that MamaGoose uses
 * 
 */
class PlasmaBall : public Bullet {
 public:
    explicit PlasmaBall(QGraphicsItem* parent = 0);
};


#endif  // INCLUDE_PLASMABALL_HPP_
