/***************************************************
*	Module Name		:	bluetooth_ui
*	Engineer		:	Gloaming
*	Target Device	:	Android arm64-V8 or Mingw
*	Tool versions	:	Qt5.12.5 android-sdk-30 android-ndk-19c
*	Create Date		:	2021-1-7
*	Revision		:	v1.0
*	Description		:   实现蓝牙的扫描与连接，通过socket发送与接收数据。
*   Notice          :   需要手动打开手机定位才能工作，搜索到蓝牙后在列表双击即可进行连接。 但只能连接4.0版本下的蓝牙。主界面通过setting进入蓝牙连接，软件没有图标，等项目完成了就完善。
**************************************************/
#include "mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,m_Ui(NULL)
    ,m_MyBlt(NULL)
{
    QScreen *screen=QGuiApplication::primaryScreen();
    QRect rect=screen->availableGeometry();
    setGeometry(0,0,rect.width(),rect.height());//主界面必须要设置大小
    m_Ui =new MainForm(this);
    m_Ui->setGeometry(0,0,rect.width(),rect.height());
    m_Ui->resize(rect.width(),rect.height());
    connect(m_Ui,&MainForm::pressSetting,this,&MyMainWindow::creatSetting);
    connect(m_Ui,&MainForm::sendDateSig,this,&MyMainWindow::sendDate);
}

MyMainWindow::~MyMainWindow()
{
}
void MyMainWindow::creatSetting()
{
    m_Ui->hide();
    if(m_MyBlt== NULL)
    {
        m_MyBlt =new MyBluetooth(this);
        m_MyBlt->initMyBluetooth(this);
        qDebug()<<"width="<<this->width()<<"height="<<this->height();
        m_MyBlt->resize(this->width(),this->height());
        m_MyBlt->show();
    }
    else
    {
        qDebug()<<"width="<<this->width();
        m_MyBlt->show();
    }
    connect(m_MyBlt,&MyBluetooth::Back_released,this,&MyMainWindow::reBack);

    connect(m_MyBlt->m_Blue_Socket,&QBluetoothSocket::readyRead,this,&MyMainWindow::recDate);//

}
void MyMainWindow::reBack()
{
    if(m_MyBlt== NULL)
    {
        exit(0);
    }
    else
    {

        m_MyBlt->hide();
        m_Ui->show();
    }
}

void MyMainWindow::sendDate()
{
    if(m_MyBlt== NULL)
    {

    }
    else
    {
        QByteArray m_arrayData;
        QString m_str;
        m_str=m_Ui->ui->TE_Textin->toPlainText();
        m_arrayData = m_str.toUtf8();
        m_MyBlt->m_Blue_Socket->write(m_arrayData);
    }
}

void MyMainWindow::recDate()
{
    QByteArray m_line = m_MyBlt->m_Blue_Socket->readAll();
    QString m_strData(m_line);
    m_Ui->ui->TB_RecShow->append(m_strData);
}
