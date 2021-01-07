#ifndef MYBLUETOOTH_H
#define MYBLUETOOTH_H

#include <QWidget>
#include <QtBluetooth>
#include <QBluetoothSocket>
#include <QBluetoothAddress>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLatin1String>
#include <QString>
#include <QList>
#include <QListWidgetItem>
#include <QDebug>
#include <QMessageBox>

#define m_Debug 0   //for debug

#if m_Debug
#include "qlog.h"
#endif

static QLatin1String s_ServiceUuid("00001101-0000-1000-8000-00805F9B34FB");//低版本蓝牙通用的UUID，4.0的BLE蓝牙不支持此类UUID

namespace Ui {
class MyBluetooth;
}

class MyBluetooth : public QWidget
{
    Q_OBJECT

public:
    explicit MyBluetooth(QWidget *parent = nullptr);
    ~MyBluetooth();
    void initMyBluetooth(QWidget *parent = nullptr);
    void MyScanFinshed();
signals:
    void Back_released();

private slots:
    void on_PB_Scanner_clicked();
    void blueDiscovery_ToList(const QBluetoothDeviceInfo& info);

    void on_LW_Bluetooth_itemActivated(QListWidgetItem *item);

    void on_PB_Back_released();
public:
    QBluetoothSocket * m_Blue_Socket;//蓝牙配对以及传输类 用户需要在主程序中使用到数据传输，因此定义为公开类


private:
    Ui::MyBluetooth *ui;
    QBluetoothLocalDevice * m_Blue_Local_Device;//本地设备类 进行一系列本地配置
    QBluetoothDeviceDiscoveryAgent * m_Blue_DiscoveryAgent;//对蓝牙进行搜寻类
    QListWidgetItem  *m_Item;
};

#endif // MYBLUETOOTH_H
