#ifndef TD_BUILD_TOWER_ICON
#define TD_BUILD_TOWER_ICON

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "game.hpp"
#include "tower.hpp"

class BuildTowerIcon: public QGraphicsPixmapItem {
public:
    BuildTowerIcon(Game* game, QGraphicsItem* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
private:
    Game* game_;
};




#endif