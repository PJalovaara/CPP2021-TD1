#include <QApplication>
#include "editor.hpp"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Editor* editor = new Editor();
	editor->show();

    return a.exec();
}
