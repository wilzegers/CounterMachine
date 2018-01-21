#include "MainWindow.h"
#include <QApplication>

#include "Processing/Parser.h"

int main(int argc, char *argv[])
{
    DEBUGFUN();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
