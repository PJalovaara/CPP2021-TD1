#ifndef TD_MENU
#define TD_MENU

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QString>
#include <QList>
#include <QPointF>
#include <QTimer>
#include <QLineEdit>
#include <QProgressBar>

class Menu : public QGraphicsView{
    Q_OBJECT
public:
    // member functions
    Menu();
    void mousePressEvent(QMouseEvent* event);
    QGraphicsScene* GetScene();

public slots:
    void level1();
	void level2();
	void level3();
	void level4();
	void level5();

private:
    QGraphicsScene* scene_;
};
#endif