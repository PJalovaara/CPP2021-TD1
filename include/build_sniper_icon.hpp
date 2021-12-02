#ifndef TD_BUILD_SNIPER_ICON
#define TD_BUILD_SNIPER_ICON

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "game.hpp"

class BuildSniperIcon: public QGraphicsPixmapItem {
public:
    BuildSniperIcon(Game* game, QGraphicsItem* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
private:
    Game* game_;
    int price_;
};





#endif