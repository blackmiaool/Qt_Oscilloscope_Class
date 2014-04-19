#include "mqinternet.h"
#include "ui_mqinternet.h"

MQInternet::MQInternet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MQInternet)
{
    ui->setupUi(this);

    server = new QTcpServer();
    client = new QTcpSocket(this);
    ip_client_state=new QLabel("no client");
    ip_state=new QLabel(QString("IP:")+GetLocalIPAddress());
    ui->lineEdit_2->setText(GetLocalIPAddress());
    ui->lineEdit->setText("3333");
    connect_state=new QLabel("state:free");

    this->statusBar()->addWidget(ip_state);
    this->statusBar()->addWidget(connect_state);
    this->statusBar()->addWidget(ip_client_state);

    connect(client,SIGNAL( stateChanged(QAbstractSocket::SocketState)),this,SLOT(connecte_stateChanged(QAbstractSocket::SocketState)));
 //
    connect(client,SIGNAL( readyRead()),this,SLOT(client_read()));
    this->setWindowTitle(tr("小喵TCP/IP调试助手"));
    QSettings *read=new QSettings("hahaya.ini",QSettings::IniFormat);
    ui->lineEdit_4->setText(read->value("name/name1").toString());



//    client_list_point=new QLineEdit("1");
//    QList<QLineEdit> client_list;
//    client_list.append(*client_list_point);
//    client_list_point==new QLineEdit("1");

//    client_list.append(*client_list_point);


       slm = new QStringListModel(this);
       sl = new QStringList();
//       sl->append("asdfsadfsa");
//       sl->append("asdfsadfsa");
//       sl->append("asdfsadfsa");
//       slm->setStringList(*sl);
       ui->listView->setModel(slm);
       list_fresh();

    this->setFocus();
      //notifyUser();
      //::NotifyBootConfigStatus()
    //::NotifyBootConfigStatus(true);
    this->setWindowOpacity(0.8);

    ui->comboBox->setCurrentIndex(1);
    on_pushButton_2_clicked();
    pic=new QPixmap();


    timer = new QTimer();
    this->connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    timer->start( 200 );


}

MQInternet::~MQInternet()
{
    delete ui;
}

typedef unsigned short u16;
typedef unsigned char u8;
void MQInternet::onTimerOut()
{
    QByteArray mybuf;  //传输  你也可以加图像识别
    JOYINFOEX JoyInfo;
    QString s12;
    static u8 filter_cnt=0;
    static u16 x[5];
    static u16 y[5];
    static u16 r[5];
    static u16 z[5];
    static u16* joy_val[4]={x,y,r,z};



    mybuf.resize(4);
//  joyGetPosEx(JOYSTICKID1,&JoyInfo);//x y 左摇杆  ZR右摇杆  方向键用不了  数值0-255 正常7aff

//    x[filter_cnt]=JoyInfo.dwXpos;
//    y[filter_cnt]=JoyInfo.dwYpos;
//    r[filter_cnt]=JoyInfo.dwRpos;
//    z[filter_cnt]=JoyInfo.dwZpos;
//    filter_cnt++;

  //  ui->textEdit->append(s12.sprintf("%x",JoyInfo.dwPOV));
   // ui->textEdit->append(s12.sprintf("   %x",JoyInfo.dwUpos));
//    if(filter_cnt==5)
//    {
//        filter_cnt=0;
//        for(short i=0;i<4;i++)
//        {
//            for(short j=0;j<5;j++)
//            {
//                for(short k=0;k<4;k++)
//                {
//                    if(joy_val[i][k]<joy_val[i][k+1])
//                    {
//                        joy_val[i][k]^=joy_val[i][k+1];
//                        joy_val[i][k+1]^=joy_val[i][k];
//                        joy_val[i][k]^=joy_val[i][k+1];
//                    }
//                }
//            }

//        }
//        vs1->setValue(y[2]*100/0xffff);
//        dl1->setValue(x[2]*100/0xffff);
//        ui->textEdit->append(s12.sprintf("             %x",x[2]));

//    }
//    for(short i=0;i<4;i++)
//        mybuf[i]=0;
//    if(vs1->value()>80)
//        mybuf[0] = 2;
//    if(vs1->value()<20)
//        mybuf[0] = 1;



    if(JoyInfo.dwXpos==0x7aff && JoyInfo.dwYpos==0x7aff )
        mybuf[0] = 5;
    else if(JoyInfo.dwXpos<0x1000 )
        mybuf[0] = 3;
    else if(JoyInfo.dwXpos>0xf000 )
        mybuf[0] = 4;
    else if(JoyInfo.dwYpos<0x7aff )
        mybuf[0] = 1;
    else if(JoyInfo.dwYpos>0x7aff )
        mybuf[0] = 2;

    if(JoyInfo.dwZpos<0x1000 )
        mybuf[1] = 1;
    else if(JoyInfo.dwZpos>0xf000 )
        mybuf[1] = 2;
    else
        mybuf[1] = 0;
    if(JoyInfo.dwRpos<0x1000 )
        mybuf[2] = 1;
    else if(JoyInfo.dwRpos>0xf000 )
        mybuf[2] = 2;
    else
        mybuf[2] = 0;
    mybuf[3] = 0;

    for(int i=0;i<clientlist.size();i++)
        clientlist.at(i)->write(mybuf);



    ui->textEdit->append(mybuf);
    //ui->lcdNumber->display(s12.sprintf("%x",JoyInfo.dwButtons));
}





















void MQInternet::client_read()//zuoweicongji
{
//    ui->textEdit->append(QString("R")+QString("[")+QTime::currentTime().toString()+QString("]")+QString::fromUtf8(client->readAll()));
    QString str;
    QTime   time1;
    str=QString::fromUtf8(client->readAll());

    if(str.left(5)==QString("leave")||str.left(5)==QString("comee"))
    {
        cmd_process(str);

        return ;
    }
    ui->textEdit->setTextColor(QColor(0,0,255));
    ui->textEdit->append(str.left(20).simplified()+QString("  ")+time1.currentTime().toString());
    ui->textEdit->setTextColor(Qt::black);
    ui->textEdit->append(str.right(str.length()-20));
}

void clientConnection::setbody(QTcpSocket * incomeclient)
{
    client_body=incomeclient;
}
QTcpSocket* clientConnection::getbody()
{
    return this->client_body;
}
QString clientConnection::getIP()
{
    return "s";
}
QString clientConnection::getname()
{
    return "s";
}
void MQInternet::acceptConnection()
{

    QTcpSocket* clientthis=server->nextPendingConnection();
    clientlist.append(clientthis);
//    sl->append(clientthis->peerAddress().toString());
//    slm->setStringList(*sl);
    list_fresh();

    //connect(clientConnection,SIGNAL( stateChanged(QAbstractSocket::SocketState)),
   //            this,SLOT(connecte_stateChanged(QAbstractSocket::SocketState)));
    ip_client_state->setText(QString("%1").arg(clientlist.size())+"client ");
    connect_state->setText("state:connected");
    //qDebug()<<"client:"<<clientConnection->localAddress().toString();



    qsmap=new QSignalMapper(this);
    connect(clientthis,SIGNAL(readyRead()),qsmap,SLOT(map()));//用在生成socket管理中，socket在
    qsmap->setMapping(clientthis,clientthis);//设置一个信号源与传递参数（mapped的参数）
    connect(qsmap,SIGNAL(mapped(QObject*)),this,SLOT(readClient(QObject*)));

    qsmap=new QSignalMapper(this);
    connect(clientthis,SIGNAL(stateChanged(QAbstractSocket::SocketState)),qsmap,SLOT(map()));//用在生成socket管理中，socket在
    qsmap->setMapping(clientthis,currentpQTcpSocket_socketstate.set(clientthis,clientthis->state()));//设置一个信号源与传递参数（mapped的参数）
    connect(qsmap,SIGNAL(mapped(QObject*)),this,SLOT(client_state_handle(QObject*)));

    for(int i=0;i<clientlist.size();i++)
    {
        if(clientlist.at(i)!=clientthis)
        {
            clientlist.at(i)->write((QString("comee")+clientthis->peerAddress().toString()).toUtf8());
            clientthis->write((QString("comee")+clientlist.at(i)->peerAddress().toString()).toUtf8());
        }
    }


}
void MQInternet::cmd_process(QString come)
{
    bool last=1;
  //  ui->textEdit->append(come);
    short i=0;
    if(come.left(5)==QString("leave"))
    {
        for(i=5;i<come.length();i++)
        {
            if((!(come.at(i)==QChar('.'))&&(!(come.at(i).isNumber()))))
            {
                sl->removeOne(come.mid(5,i-5));
                slm->setStringList(*sl);
                cmd_process(come.right(come.length()-i));
                break;

            }
            else if((i==come.length()-1)&&last)
            {
                sl->removeOne(come.mid(5,i-4));
                slm->setStringList(*sl);
                last=0;

            }
        }
    }
    else if(come.left(5)==QString("comee"))
    {
        for(i=5;i<come.length();i++)
        {

            if((!(come.at(i)==QChar('.'))&&(!(come.at(i).isNumber()))))
            {
                sl->append(come.mid(5,i-5));
                slm->setStringList(*sl);
                cmd_process(come.right(come.length()-i));
                break;
            }
            else if((i==come.length()-1)&&last)
            {
                sl->append(come.mid(5,i-4));
                slm->setStringList(*sl);
                last=0;
            }
        }
    }


}
void MQInternet::client_state_handle(QObject* ddd)
{
    pQTcpSocket_socketstate *fff;
    QTcpSocket *currentsocket;
    fff=(pQTcpSocket_socketstate *)ddd;
    for(int i=0;i<clientlist.size();i++)
    {
        if(clientlist.at(i)->state()!=3)
            currentsocket=clientlist.at(i);

    }
    ui->textEdit->append(currentsocket->peerAddress().toString());
    ui->textEdit->append(QString("%1").arg(currentsocket->state()));
    switch(currentsocket->state())
    {
    case(QAbstractSocket::UnconnectedState):
     //   ui->textEdit->append("UnconnectedState");
   //     qDebug()<<"UnconnectedState";
        break;
    case(QAbstractSocket::HostLookupState):
    //    ui->textEdit->append("HostLookupState");
    //    qDebug()<<"HostLookupState";
        break;
    case(QAbstractSocket::ConnectingState):
   //     ui->textEdit->append("ConnectingState");
    //    qDebug()<<"ConnectingState";
        break;
    case(QAbstractSocket::ConnectedState):
       // ui->textEdit->append("ConnectedState");
     //   qDebug()<<"ConnectedState";

     //   delete(fff->pQTcpSocket);
        break;
    case(QAbstractSocket::BoundState):
     //   ui->textEdit->append("BoundState");
    //    qDebug()<<"BoundState";
        break;
    case(QAbstractSocket::ClosingState):
    //   ui->textEdit->append("ClosingState");
    //    qDebug()<<"ClosingState";
        currentsocket->disconnect();
        clientlist.removeOne(currentsocket);
        list_fresh();
        for(int i=0;i<clientlist.size();i++)
        {
            clientlist.at(i)->write((QString("leave")+currentsocket->peerAddress().toString()).toUtf8());
        }
        break;
//    case(QAbstractSocket::ListeningState):
//        break;

    }
}
QObject* pQTcpSocket_socketstate::set(QTcpSocket *s1,QAbstractSocket::SocketState s2)
{

    this->pQTcpSocket=s1;
    this->state=s2;
    return this;
}
typedef unsigned long u32;
typedef unsigned char u8;
void MQInternet::setlabel(QLabel* image_l)
{
    image_label=image_l;
}
u8 image2show[90000];
void MQInternet::readClient(QObject* ccomeclient)//as server
{
    char* str;
    static u8 show_flag;
    static u32 lenth=0;
    static u8 state=0;
    static u32 cnt=0;
    static u8 state2=0;
    static u32 lenth_beifen;
    u32 pkg_lenth=0;
    QTcpSocket *comeclient=(QTcpSocket *)ccomeclient;
    QByteArray pkg_this=comeclient->readAll();
    str=pkg_this.data();
    pkg_lenth=pkg_this.length();
    for(u32 i=0;i<pkg_lenth;i++)
    {
        u8 byte_this=str[i];

        switch(state)
        {

        case 0:
            {

                switch(state2)
                {
                case 0:
                    if(byte_this==0xf4)
                    {
                        state2=1;
                    }
                    break;
                case 1:
                    if(byte_this==0xf3)
                    {
                        state2=2;
                    }
                    else
                        state2=0;
                    break;
                case 2:
                    if(byte_this==0xf2)
                    {

                        state2=3;
                    }
                    else
                        state2=0;
                    break;

                break;
                case 3:
                    if(byte_this==0x04)
                    {

                        state2=4;
                    }
                    else
                        state2=0;
                    break;
                case 4:
                    if(byte_this==0x03)
                    {

                        state2=5;
                    }
                    else
                        state2=0;
                    break;
                case 5:
                    if(byte_this==0x02)
                    {

                        state2=0;
                        state=1;
                        lenth=0;
                        cnt=0;
                    }
                    else
                        state2=0;
                    break;
                }
                break;


            }

        case 1:
        case 2:
        case 3:
        case 4:
            *(((u8 *)(&lenth))+(state-1))=byte_this;
            state++;
            if(state==5)
                lenth_beifen=lenth;
              ui->lineEdit_3->setText(QString("%1").arg(lenth));
            break;
        case 5:
            lenth--;
            image2show[cnt++]=byte_this;
            if(lenth==0)
            {
                pic->loadFromData((const u8*)image2show,lenth_beifen);

                this->image_label->setPixmap(*pic);
                state=0;
            }

            break;


        }


    }
    //   if(state<6)
 //ui->textEdit->append(pkg_this.toHex());

}
void MQInternet::list_fresh()
{
    QStringList* newlist;
    newlist=new QStringList();
    for(int i=0;i<clientlist.size();i++)
    {
        newlist->append(clientlist.at(i)->objectName()+QString(" "+clientlist.at(i)->peerAddress().toString()));
    }
    slm->setStringList(*newlist);

}

void MQInternet::connecte_stateChanged(QAbstractSocket::SocketState state)
{
  //  connect_state->setText(QString("state:")+state.);
    switch(state)
    {
    case(QAbstractSocket::UnconnectedState):
        connect_state->setText("UnconnectedState");
        if(ui->comboBox->currentIndex()==0)
        ui->pushButton_2->setText("connect");
        else
            ip_client_state->setText("no client ");
        break;
    case(QAbstractSocket::HostLookupState):
        connect_state->setText("HostLookupState");
        break;
    case(QAbstractSocket::ConnectingState):
        connect_state->setText("ConnectingState");
         if(ui->comboBox->currentIndex()==0)
        ui->pushButton_2->setText("disconnect");

        ui->pushButton->setEnabled(true);
        break;
    case(QAbstractSocket::BoundState):
        connect_state->setText("BoundState");
        break;
    case(QAbstractSocket::ClosingState):
        connect_state->setText("ClosingState");
        break;
    case(QAbstractSocket::ListeningState):
        connect_state->setText("ListeningState");
        break;
    }


}

QString MQInternet::GetLocalIPAddress()
{
         QString vAddress;

         #ifdef _WIN32
         QHostInfo vHostInfo = QHostInfo::fromName(QHostInfo::localHostName());
         //qDebug()<< QHostInfo::localHostName();
         QList<QHostAddress> vAddressList = vHostInfo.addresses();
         #else
         QList<QHostAddress> vAddressList = QNetworkInterface::allAddresses();
         #endif
         for(int i = 0; i < vAddressList.size(); i++)
         {
                   if(!vAddressList.at(i).isNull() &&
                            vAddressList.at(i) != QHostAddress::LocalHost &&
                            vAddressList.at(i).protocol() ==  QAbstractSocket::IPv4Protocol)
                   {
                            vAddress = vAddressList.at(i).toString();
                            qDebug()<<vAddress;
                            break;
                   }
         }
         return vAddress;
}



void MQInternet::on_comboBox_currentIndexChanged(int index)
{
    if(index==1)
    {
        ui->pushButton_2->setText("listen");
    }
    else
    {
        ui->pushButton_2->setText("connect");
        ui->pushButton_2->setEnabled(true);
    }

}

void MQInternet::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex()==0)
    {

        QTime time1;
        QString nichengzhanwei;
        QString tianchong;
        tianchong.fill(' ',20);
        if(ui->lineEdit_4->text().length()<20)
        {
            nichengzhanwei=ui->lineEdit_4->text();
            nichengzhanwei.append(tianchong.left(20-ui->lineEdit_4->text().length()));
        }
        else nichengzhanwei=ui->lineEdit_4->text().left(20);

        client->write(nichengzhanwei.toUtf8()+ui->lineEdit_3->text().toUtf8());
        ui->textEdit->setTextColor(QColor(0,128,64));
        ui->textEdit->append(ui->lineEdit_4->text()+QString("  ")+time1.currentTime().toString());
        ui->textEdit->setTextColor(Qt::black);
        ui->textEdit->append(ui->lineEdit_3->text());
    }
    else
    {
        QTime time1;
        QString nichengzhanwei;
        QString tianchong;
        tianchong.fill(' ',20);
        if(ui->lineEdit_4->text().length()<20)
        {
            nichengzhanwei=ui->lineEdit_4->text();
            nichengzhanwei.append(tianchong.left(20-ui->lineEdit_4->text().length()));
        }
        else nichengzhanwei=ui->lineEdit_4->text().left(20);
        for(int i=0;i<clientlist.size();i++)
            clientlist.at(i)->write(nichengzhanwei.toUtf8()+ui->lineEdit_3->text().toUtf8());
      //  clientthis->write(nichengzhanwei.toUtf8()+ui->lineEdit_3->text().toUtf8());
    //   ui->textEdit->append(QString("T")+QString("[")+time1.currentTime().toString()+QString("]")+ui->lineEdit_3->text());
        ui->textEdit->setTextColor(QColor(0,128,64));
        ui->textEdit->append(ui->lineEdit_4->text()+QString("  ")+time1.currentTime().toString());
        ui->textEdit->setTextColor(Qt::black);
        ui->textEdit->append(ui->lineEdit_3->text());
    }

}

void MQInternet::on_pushButton_2_clicked()
{
    if(ui->comboBox->currentIndex()==0)
    {
      //  client = new QTcpSocket(this);
       // client->disconnect();
        if(ui->pushButton_2->text()==QString("connect"))
        {

            client->connectToHost(QHostAddress(ui->lineEdit_2->text()), ui->lineEdit->text().toInt());
        }
        else
        {

            sl->clear();
            slm->setStringList(*sl);
            ui->pushButton->setEnabled(false);
            client->abort();
        }
    }
    else
    {

        if(!server->listen(QHostAddress::Any,ui->lineEdit->text().toInt()))
        {  //监听本地主机的6666端口，如果出错就输出错误信息，并关闭
            qDebug() << server->errorString();
            close();
        }
        ui->pushButton->setEnabled(true);
        connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
        ui->pushButton_2->setEnabled(false);
    }
}

void MQInternet::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->pushButton_2->setEnabled(true);
}

void MQInternet::on_lineEdit_textChanged(const QString &arg1)
{

    ui->pushButton_2->setEnabled(true);
}

void MQInternet::on_lineEdit_3_returnPressed()
{
    if(ui->pushButton->isEnabled())
    {
        emit(ui->pushButton->clicked());
        ui->lineEdit_3->clear();
    }

}

void MQInternet::on_lineEdit_4_textChanged(const QString &arg1)
{
     QSettings *read=new QSettings("hahaya.ini",QSettings::IniFormat);
     read->setValue("name/name1",ui->lineEdit_4->text());
}

