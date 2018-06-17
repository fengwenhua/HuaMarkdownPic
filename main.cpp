#include "mainwindow.h"
#include <QApplication>

#pragma comment(lib,"qiniu.lib")



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QDesktopWidget *deskTop=QApplication::desktop();
//    qDebug()<<"desktop->width()="<<deskTop->width();
//    qDebug()<<"deskTop->height()="<<deskTop->height();
//    qDebug()<<"w.width()="<< w.width();
//    qDebug()<<"w.height()="<<w.height();
    w.setWindowTitle(QString::fromLocal8Bit("HMP"));

    w.move((deskTop->width() - w.width())/2+20, (deskTop->height() - w.height())-70);
    w.show();
    w.keepLoadPic();

    return a.exec();
}
