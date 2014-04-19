#ifndef MQSERIAL_H
#define MQSERIAL_H


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
namespace Ui {
class MQSerial;
}

class MQSerial : public QMainWindow
{
    Q_OBJECT

public:

     bool dakaibuttonflag;
    // tishi *cuowutishi;
    explicit MQSerial(QWidget *parent = 0);
    ~MQSerial();
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



    void on_verticalSlider_sliderReleased();


    void on_dial_sliderReleased();

private:
    Win_QextSerialPort *myCom;
    Ui::MQSerial *ui;
    int canshubiao[4];
    QextSerialEnumerator enumerator;
    long receivenum;
    Readcom comm;
    QString alltext;
    int sendnum;
    //bool event(QEvent *event);
    QLabel* btm_state;

};

#endif // MQSERIAL_H
