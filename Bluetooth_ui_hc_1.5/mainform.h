#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "mybluetooth.h"
#include <QPushButton>
#include <QByteArray>
#include <QDebug>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();
    void sendDate();
    void settingBlt();
signals:
    void pressSetting();
    void sendDateSig();

public:
     Ui::MainForm *ui;
private:
    MyBluetooth * m_MyBltUi;
};

#endif // MAINFORM_H
