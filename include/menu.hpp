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
    QList<QList<QPointF>> ReadPathsFromFile(const QString& filename);

public slots:
    void StartLevel1();
	void StartLevel2();
	void StartLevel3();
	void StartLevel4();
	void StartLevel5();
    void StartCustom();
    void StartEditor();

private:
    QGraphicsScene* scene_;
};
#endif