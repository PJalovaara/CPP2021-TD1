#ifndef TD_GAME
#define TD_GAME

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>


class Game : public QGraphicsView{
public:
    // member functions
    Game();
    void mousePressEvent(QMouseEvent* event);
    // member attributes
    //QGraphicsScene* GetScene();
    QGraphicsScene* scene;
private:
    
};






#endif