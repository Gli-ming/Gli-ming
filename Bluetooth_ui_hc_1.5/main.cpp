#include "mymainwindow.h"
#include "ui_Mainform.h"
#include <QWidget>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow w;
    w.show();
    return a.exec();
}
