#include <QApplication>
#include "game.hpp"

// This is an example of how to use doxygen
/**
 * @brief Here we put a brief description, that will end on the first dot, newline etc.
 * 
 * Meaning that this here is the detailed description. This can be much longer than the brief
 * description.
 * 
 * @param argc using (at)param means that doxygen will create documentation for this parameter
 * @param argv meaning that we can say something about the parameter in hand
 * @return int and here we can say smth about the return value
 * @see Game() this will give the user a link in the documentation to the linked function/class.
 */
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
