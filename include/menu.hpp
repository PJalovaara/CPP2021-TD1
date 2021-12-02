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
    void SetCursor(QString filename);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    bool state_;
	bool GetState();
    QGraphicsScene* GetScene();
    QGraphicsPixmapItem* GetCursor();
    void ResetCursor();
public slots:
    void level1();
	void level2();
	void level3();
	void level4();
	void level5();

signals:
    void done();

private:
    QGraphicsScene* scene_;
    QGraphicsPixmapItem* cursor_;
};
#endif