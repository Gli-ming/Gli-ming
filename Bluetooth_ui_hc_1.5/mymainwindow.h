#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "mybluetooth.h"
#include <QScreen>
#include <QRect>
#include <QGuiApplication>
#include "mainform.h"
#include "ui_mainform.h"


class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    void creatSetting();
    void reBack();
    void sendDate();
    void recDate();
private:
    MainForm * m_Ui;
    MyBluetooth* m_MyBlt;
};
#endif // MYMAINWINDOW_H
