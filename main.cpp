#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //-----------------Получение путей
        QString tPath = a.applicationDirPath();
        int tDirCount = tPath.count("/");
        QString tpath = tPath.section("/",0, tDirCount-1);

       #ifdef  Q_OS_WIN
      QString path =QString("%1").arg("C://Путь к проекту//"); // доработать
       #endif

       #ifdef Q_OS_UNIX
      QString path =QString::fromLocal8Bit("%1/").arg(tpath);
       #endif

    MainWindow w(path);
    w.show();

    return a.exec();
}
