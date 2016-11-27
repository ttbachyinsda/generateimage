#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deal.h"
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
        vga_putchar('_',255);
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
            int blue = color%8*32;
            int green = (color>>3)%8*32;
            int red = (color>>5)%8*32;
            //qDebug()<<blue<<' '<<green<<' '<<red<<endl;
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
    if (event->key()<128)
    {
        unsigned char temp=event->key();
        if ((temp>='A' && temp<='Z') || (temp>='a' && temp<='z'))
        {
        temp += ('a'-'A');
        if (modifiers && Qt::ShiftModifier)
            temp -= 'a'-'A';
        }
        vga_putchar(temp,0);
        update();
    }
    if (event->key()==Qt::Key_Return)
    {
        vga_putchar('\n',0);
        update();
    }
    if (event->key()==Qt::Key_Backspace)
    {
        changetoapp();
        update();
    }
    if (event->key()==Qt::Key_Delete)
    {
        changetoconsole();
        update();
    }
}
