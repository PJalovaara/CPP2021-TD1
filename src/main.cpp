#include <QApplication>

#include "menu.hpp"

/**
 * @brief The main function of the program
 * 
 * The function is responsible for creating the main menu of the game.
 * 
 * @param argc
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Menu* menu = new Menu();
    menu->show();

    return a.exec();
}
