#include "mainwindow.h"
#include "deal.h"
#include "box.h"
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(800,600);
    //readimage();
    vga_init();
    for (int i=0;i<100;i++)
        vga_putchar('_');
    qDebug()<<"insert end"<<endl;
}

MainWindow::~MainWindow()
{
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (int i=0;i<600;i++)
        for (int j=0;j<800;j++)
        {
            int color=memorie[((i>>1)<<WINDOW_LEFT)+(j>>1)];
            int blue = color%8*255/7;
            int green = (color>>3)%8*255/7;
            int red = (color>>6)%8*255/7;
            QColor qc(red,green,blue);
            painter.setPen(qc);
            painter.drawPoint(j,i);
        }
}
void MainWindow::paint()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    Qt::KeyboardModifiers modifiers = event->modifiers();
    if (iscommand)
    {
    if (event->key()<128)
    {
        unsigned char temp=event->key();
        if ((temp>='A' && temp<='Z') || (temp>='a' && temp<='z'))
        {
        temp += ('a'-'A');
        if (modifiers && Qt::ShiftModifier)
            temp -= 'a'-'A';
        }
        vga_putchar(temp);
        update();
    }
    if (event->key()==Qt::Key_Return)
    {
        vga_putchar('\n');
        update();
    }
    if (event->key()==Qt::Key_Backspace)
    {
        changetoapp();
        boxbegingame(memorie+0);
        update();
    }
    }
    else
    {
        if (event->key()<128)
        {
            unsigned char temp=event->key();
            boxkeypress(temp);
            update();
        }
        if (event->key()==Qt::Key_Delete)
        {
            changetoconsole();
            update();
        }
    }
}
