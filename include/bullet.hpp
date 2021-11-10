#ifndef TD_BULLET
#define TD_BULLET

#include <QGraphicsPixmapItem>
#include <QObject>


class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT // Macro needed to work with signals and slots (and it needs to inherit from QObject)
public:
    Bullet(QGraphicsItem* parent = 0);

public slots:
    void Move();
private:
};




#endif