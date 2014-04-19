#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qextserialport.h"

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
#include <QSettings>
#include "mqinternet.h"

//#include "wenjianchuang.h"
namespace Ui {
class MainWindow;
}
class dds : public QLabel
{
    Q_OBJECT
public:
    QPlainTextEdit *bb;
    bool event(QEvent *event );
    dds(QWidget* d);
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTcpServer *server;
    QTcpSocket *client;

     bool dakaibuttonflag;
    // tishi *cuowutishi;

    explicit MainWindow(QWidget *parent = 0);
    dds *d1;
    ~MainWindow();
public slots:
    void readMyCom();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();



    void on_comboBox_2_activated(int);



    void on_comboBox_3_activated(int index);

    void on_comboBox_5_activated(int index);



    void on_comboBox_4_activated(int index);

    void on_lineEdit_editingFinished();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_7_clicked();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

//    void on_pushButton_9_clicked();

//    void on_pushButton_10_clicked();

//    void on_pushButton_11_clicked();


    void on_verticalSlider_sliderReleased();


    void on_dial_sliderReleased();

private:
    Win_QextSerialPort *myCom;
    Ui::MainWindow *ui;
    int canshubiao[4];
    QextSerialEnumerator enumerator;
    long receivenum;
    Readcom comm;
    QString alltext;
    int sendnum;
    //bool event(QEvent *event);
    MQInternet *MQI;
    QLabel* btm_state;
};


#endif // MAINWINDOW_H
