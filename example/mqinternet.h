#ifndef MQINTERNET_H
#define MQINTERNET_H

#include <QMainWindow>
#include "tishi.h"
#include "QLabel"
#include "QPlainTextEdit"



#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include "QList"
#include <QLineEdit>
#include <QSlider>
#include <QSignalMapper>
#include <QStringListModel>
#include "QSettings"
#include "QTime"
#include "QtNetwork/QtNetwork"
#include "QTimer.h"
#include "windows.h"
#include "winuser.h"
#include "mmsystem.h"
#include <QSlider>
#include <QDial>
#pragma comment(lib,"winmm.lib")
namespace Ui {
class MQInternet;
}





class clientConnection:public QObject
{
    Q_OBJECT
public:

    QString getname(void);
    QString getIP(void);
    void setbody(QTcpSocket *);
    QTcpSocket * getbody(void);

private:
    QTcpSocket *client_body;
    QString name;
    QString IP;
};






class pQTcpSocket_socketstate:QObject
{
    Q_OBJECT
public:
    QObject *set(QTcpSocket *,QAbstractSocket::SocketState);
    QTcpSocket* pQTcpSocket;
    QAbstractSocket::SocketState state;
    QObject s;
};





class MQInternet : public QMainWindow
{
    Q_OBJECT

public:
    explicit MQInternet(QWidget *parent = 0);
    ~MQInternet();
      QSlider* vs1;
      QDial* dl1;
    void setlabel(QLabel* );
private slots:

    void onTimerOut();
private:
    Ui::MQInternet *ui;


    QTimer *timer;










    QPixmap *pic;

    QLabel* image_label;

    QTcpServer *server;
    QTcpSocket *client;
    QLabel* ip_state;
    QLabel* connect_state;
    QLabel* ip_client_state;
    QPushButton* ss;
    QList<QLineEdit>* client_list;
    QString GetLocalIPAddress(void);
    QLineEdit* client_list_point;
    QSignalMapper *qsmap;
    QList<QTcpSocket *> clientlist;
    QStringListModel* slm;
     QStringList* sl;
    pQTcpSocket_socketstate currentpQTcpSocket_socketstate;
    void cmd_process(QString);
    void list_fresh(void);
  QTimer timer1;

private slots:
    void acceptConnection(void);
    void readClient(QObject*);
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void connecte_stateChanged(QAbstractSocket::SocketState state);
    void client_read();

    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_3_returnPressed();
    void client_state_handle(QObject *);
  //  void sendmessagetologic(QObject* ssocket);
    void on_lineEdit_4_textChanged(const QString &arg1);




};

#endif // MQINTERNET_H
