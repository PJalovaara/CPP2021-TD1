#include <QApplication>
#include "game.hpp"

int main(int argc, char *argv[])
{
    QList<QPointF> path;
    path << QPoint(0,0) << QPoint(400, 400);
    QList<QList<QPointF>> paths;
    paths << path;
    QApplication a(argc, argv);
    Game* game = new Game(paths);
	game->show();

    return a.exec();
}
