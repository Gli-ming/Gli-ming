#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
  ,m_MyBltUi(NULL)
{
    ui->setupUi(this);

    connect(ui->PB_Send,&QPushButton::clicked,this,&MainForm::sendDate);
    connect(ui->PB_Setting,&QPushButton::clicked,this,&MainForm::settingBlt);
}

MainForm::~MainForm()
{
    delete ui;
}
void MainForm::sendDate()
{
    emit this->sendDateSig();

}
void MainForm::settingBlt()
{
    emit this->pressSetting();
}

