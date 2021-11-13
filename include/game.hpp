#ifndef TD_GAME
#define TD_GAME

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QString>

#include "tower.hpp"

class Game : public QGraphicsView{
public:
    // member functions
    Game();
    void SetCursor(QString filename);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    
    Tower* GetBuild();
    void SetBuild(Tower* newBuild);
    QGraphicsScene* GetScene();
    QGraphicsPixmapItem* GetCursor();
    void ResetCursor();
    
private:
    QGraphicsScene* scene_;
    Tower* build_;
    QGraphicsPixmapItem* cursor_;
};


#endif