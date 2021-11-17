#ifndef TD_GAME
#define TD_GAME

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QString>
#include <QList>
#include <QPointF>
#include <QTimer>

#include "tower.hpp"
#include "mamagoose.hpp"

class Game : public QGraphicsView{
    Q_OBJECT
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

    void CreatePath();
    void CreateEnemies(int numberOfEnemies);

public slots:
    void SpawnEnemy();

    
private:
    QGraphicsScene* scene_;
    Tower* build_;
    QGraphicsPixmapItem* cursor_;
    QTimer* enemySpawnTimer_;
    int enemiesSpawned_;
    int maxNoOfEnemies_;
    QList<QPointF> pathPoints_;
};


#endif