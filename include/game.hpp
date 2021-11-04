#ifndef TD_GAME
#define TD_GAME

#include <QGraphicsView>
#include <QGraphicsScene>


class Game : public QGraphicsView{
public:
    // member functions
    Game();
    // member attributes
    QGraphicsScene* scene;
private:
};






#endif