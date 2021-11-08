#include <QApplication>
#include "game.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game* game = new Game(); // inherits from QGraphicsView
    // Hence must call show method
    game->show();

    return a.exec();
}
