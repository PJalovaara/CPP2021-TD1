#ifndef TD_BUILD_TOWER_ICON
#define TD_BUILD_TOWER_ICON

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "game.hpp"
#include "tower.hpp"

class BuildMamaIcon: public QGraphicsPixmapItem {
public:
    BuildMamaIcon(Game* game, QGraphicsItem* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
private:
    Game* game_;
    int price_;
};




#endif