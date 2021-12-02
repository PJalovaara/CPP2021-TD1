#include <QApplication>
#include "game.hpp"
#include "editor.hpp"
#include "menu.hpp"
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
    QApplication a(argc, argv);
	Menu* menu = new Menu();
	menu->show();

    // Level Editor
    Editor* editor = new Editor();
    editor->show();

    return a.exec();
}
