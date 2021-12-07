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

#include "game.hpp"
#include "editor.hpp"

class Menu : public QGraphicsView{
    Q_OBJECT
public:
    // member functions
    Menu();
    ~Menu();
    void mousePressEvent(QMouseEvent* event);
    QGraphicsScene* GetScene();
    QList<QList<QPointF>> ReadPathsFromFile(const QString& filename);
    void closeEvent(QCloseEvent *event);

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
    QList<Game*> active_games_;
    QList<Editor*> active_editors_;
};
#endif