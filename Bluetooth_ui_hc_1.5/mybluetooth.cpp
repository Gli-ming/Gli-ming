#include "mybluetooth.h"
#include "ui_mybluetooth.h"

MyBluetooth::MyBluetooth(QWidget *parent) :
    QWidget(parent)
  ,m_Blue_Socket(NULL)
  ,ui(new Ui::MyBluetooth)
  ,m_Blue_Local_Device(NULL)
  ,m_Blue_DiscoveryAgent(NULL)
  ,m_Item(NULL)
{
    ui->setupUi(this);
}
void MyBluetooth::initMyBluetooth(QWidget *parent)
{
    m_Blue_Local_Device   = new QBluetoothLocalDevice(parent);
    m_Blue_DiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(parent);
    m_Blue_Socket         = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol,this);
    if(m_Blue_Local_Device->hostMode() == QBluetoothLocalDevice::HostPoweredOff)//如果蓝牙处于关闭状态，则申请打开
    {
#if m_Debug
        qDebug()<<"bluetooth donnot open";
        LOG("bluetooth donnot open");
#endif
        m_Blue_Local_Device->powerOn();//open
    }
    m_Blue_DiscoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);//发现所有可见设备


#if m_Debug
       // LOG("bluetooth start scanning");
#endif

    connect(m_Blue_DiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,this,&MyBluetooth::blueDiscovery_ToList);//扫描结果显示到list的监控
    connect(m_Blue_DiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::finished,this,&MyBluetooth::MyScanFinshed);//扫描结束的监控
    //接收数据的监控
   // connect(m_Blue_Socket,&QBluetoothSocket::readyRead,this,&MyBluetooth::recBluetoothDate);//放到执行处监控
}

MyBluetooth::~MyBluetooth()
{
    delete ui;
    if(m_Item != NULL)
        delete m_Item;
}
void MyBluetooth::MyScanFinshed()
{
        ui->TB_Show->append(QString("Scanner is over!"));//追加扫描完成
#if m_Debug
        qDebug()<<"we find "<<m_blue_name;
//        LOG("we finally find %s",m_blue_name.toStdString().c_str());
#endif
}
void MyBluetooth::blueDiscovery_ToList(const QBluetoothDeviceInfo& info)
{

    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
    QList<QListWidgetItem *> items =ui->LW_Bluetooth->findItems(label,Qt::MatchExactly);
       if (items.empty())
       {
           m_Item = new QListWidgetItem(label);
           QBluetoothLocalDevice::Pairing pairingStatus = m_Blue_Local_Device->pairingStatus(info.address());
           if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )//搜到的蓝牙已经进行了配对，连接时不论是否授权的设备都高显
               m_Item->setTextColor(QColor(Qt::green));
           else
               m_Item->setTextColor(QColor(Qt::black));
           ui->LW_Bluetooth->addItem(m_Item);
       }
}

void MyBluetooth::on_PB_Scanner_clicked()//扫描按键 直接通过ui到的槽函数就不连接了
{
    m_Blue_DiscoveryAgent->start();//start scan ble model
}

void MyBluetooth::on_LW_Bluetooth_itemActivated(QListWidgetItem *item)//listwidget双击项目的槽
{
       QString m_text = item->text();
       int m_index = m_text.indexOf(' ');//蓝牙地址都是使用空格隔开前后地址与名字的

       if (m_index == -1)//如果选取无效
           return;

       QBluetoothAddress m_address(m_text.left(m_index));
       QString m_name(m_text.mid(m_index + 1));
       QString m_temp_address=QString("%1").arg(m_address.toString());
#if m_Debug
       // LOG("bluetooth start scanning");
       qDebug() << "You has choice the bluetooth address is " << address;
       qDebug() << "The device is connneting.... ";
#endif
       ui->TB_Show->append(QString("你链接的蓝牙地址是：")+m_temp_address);
       ui->TB_Show->append(QString("你链接的蓝牙名字：")+m_name);
       m_Blue_Socket->connectToService(m_address, QBluetoothUuid(s_ServiceUuid) ,QIODevice::ReadWrite);

       //
       connect(m_Blue_Socket,&QBluetoothSocket::connected,this,[=]
       {
           ui->TB_Show->append(QString("successfull connnection!"));
       });

}

void MyBluetooth::on_PB_Back_released()//返回按键
{
    emit this->Back_released();
}
