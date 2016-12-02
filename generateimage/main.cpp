#include "mainwindow.h"
#include <QApplication>
#include "generatefont.h"
#include "generatebox.h"
#include "generatelevel.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();


//    generatefont("d:\\image\\console.txt");
    //generatebox("d:\\image\\num9.bmp");
    //generatelevel("d:\\image\\boxleveldata.txt");

    //return 0;
}
