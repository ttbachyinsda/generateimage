#include "mainwindow.h"
#include <QApplication>
#include "generatefont.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();


//    generatefont("d:\\image\\console.txt");

    return 0;
}
