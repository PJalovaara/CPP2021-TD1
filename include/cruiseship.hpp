#ifndef TD_CRUISESHIP
#define TD_CRUISESHIP

#include <QList>
#include <QPointF>
#include "game.hpp"
#include "enemy.hpp"

class Cruiseship : public Enemy {
    Q_OBJECT
public:
    Cruiseship(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent = 0);
public slots:
    virtual void MoveForward();
private:
};






#endif