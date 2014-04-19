#include "mqserial.h"

#include "ui_mainwindow.h"
//#include "wenjianchuang.h"
//#include "ui_wenjianchuang.h"
#include "QTextCodec"
#include <QtCore/QSettings>
#include <stdlib.h>
#include <stdio.h>
#include "tishi.h"
//#include "ui_tishi.h"
#include <QDialog>
#include <QFileDialog>
#include <fstream>
#include <stdlib.h>
#include "winbase.h"
#include "QPlainTextEdit"
#include "ui_mqserial.h"
bool ishex(char);
MQSerial::MQSerial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MQSerial)
{

    ui->setupUi(this);

    dakaibuttonflag=false;
    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
    canshubiao[0]=19;
    canshubiao[1]=3;
    canshubiao[2]=0;
    canshubiao[3]=0;
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    //d1=new dds(ui->plainTextEdit);
    receivenum =0;
    sendnum=0;

    myCom = new Win_QextSerialPort("\\\\.\\com11", QextSerialBase::EventDriven);
    dakaibuttonflag=false;
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    QString aa;
    QString path="HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM";
    QSettings *settings=new QSettings(path,QSettings::NativeFormat);
    QStringList key=settings->allKeys();
    int num=(int)key.size();
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    aa[0]=ports.size()+48;
    aa[1]=num+48;
    for(int i=0;comm.getcomm(i,"value")!="nokey"&&comm.getcomm(i,"value")!="Cannot open regedit!";i++)
    {
      ui->comboBox->addItem(comm.getcomm(i,"value"));
    }






}

MQSerial::~MQSerial()
{
    delete ui;
}
void MQSerial::readMyCom() //śÁ´ŽżÚşŻĘý

{
    QByteArray temp = myCom->readAll();
    receivenum+=temp.size();

//    char ss[20];
//  //  sprintf_s(ss,"%d",receivenum);
//    //_itoa_s(receivenum,ss,10);
//    ui->lineEdit_3->setText(ss);

    QString delta2;
    delta2=QString("%1").arg(receivenum);
    ui->lineEdit_3->setText(delta2);


    if(!ui->checkBox->isChecked())
    {
        alltext.append(temp);
        int sizesize=temp.size();
        QString ss=temp.toHex();
        for(long i=0;i<sizesize;i++)
            ss.insert(3*i," ");


        if(ui->checkBox_2->isChecked())
            ui->plainTextEdit->insertPlainText(ss);
        else
            ui->plainTextEdit->insertPlainText(temp);

       ui->plainTextEdit->moveCursor(QTextCursor::End);
    }
}



void MQSerial::on_pushButton_4_clicked()
{
  //  struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
  //  myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);
    if(dakaibuttonflag)
    {//WaitCommEvent error 22
        if(myCom->isOpen())
        {
            myCom->close();//WaitCommEvent error 22/
            ui->pushButton_4->setText("Open");
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_8->setEnabled(false);
            dakaibuttonflag=!dakaibuttonflag;
        }
    }
    else
    {
        ui->pushButton_8->setEnabled(true);
        QString ss="\\\\.\\com";
        QString zhongjian=ui->comboBox->currentText();
        ss.append(zhongjian[3]);
        if(zhongjian.length()>4)
        ss.append(zhongjian[4]);
        if(zhongjian.length()>5)
        ss.append(zhongjian[5]);
        myCom->setPortName(ss);
        if(myCom ->open(QIODevice::ReadWrite))
        {
            ui->pushButton_4->setText("Close");
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            myCom->setBaudRate((BaudRateType)canshubiao[0]);
            myCom->setDataBits((DataBitsType)canshubiao[1]);
            myCom->setParity((ParityType)canshubiao[2]);
            myCom->setStopBits((StopBitsType)canshubiao[3]);
             dakaibuttonflag=!dakaibuttonflag;
        }


    }
}

void MQSerial::on_pushButton_3_clicked()
{
    if(!ui->checkBox_3->isChecked())
    {
        if(ui->checkBox_10->isChecked())
        {
            myCom->write(ui->lineEdit->text().toLatin1().append("\n"));
            sendnum+=ui->lineEdit->text().toLatin1().size()+1;
        }
        else
        {
            myCom->write(ui->lineEdit->text().toLatin1());
            sendnum+=ui->lineEdit->text().toLatin1().size();
        }
    }
    else
    {
        QByteArray fasonghex=ui->lineEdit->text().toLatin1();
        QString fasongzhi;
        int indexjishu=0;
        QString fasongxinxi;
        while(1)
        {


            if(indexjishu+1>=fasonghex.size())
                break;
            {

                char a[3];
                if(ishex(fasonghex[indexjishu]))
                a[0]=fasonghex[indexjishu];
                else
                {
                    QString aa=tr("ŐâĘÇHEXˇ˘ËÍĹśÇ×ŁŹÄúĘäČë´íż� ");


                break;
                }
                if(ishex(fasonghex[indexjishu+1]))
                a[1]=fasonghex[indexjishu+1];
                else
                {
                    QString aa=tr("ŐâĘÇHEXˇ˘ËÍĹśÇ×ŁŹÄúĘäČë´íż� ");
                    //cuowutishi->ui->label->setText(aa);
                    //cuowutishi->show();
                break;
                }
                a[2]='\0';
                QByteArray text = QByteArray::fromHex(a);
                fasongxinxi.append(text.data());


                if(fasonghex[indexjishu+2]==' ')
                indexjishu+=3;
                else
                indexjishu+=2;


            }
        }
        if(ui->checkBox_10->isChecked())
        {
            myCom->write(fasongxinxi.insert(0,"\n").toLatin1());
            sendnum+=indexjishu/3+1+1;
        }
        else
        {
            myCom->write(fasongxinxi.toLatin1());
            sendnum+=indexjishu/3+1;
        }

    }
    QString delta3;
    delta3=QString("%1").arg(sendnum);
    ui->lineEdit_3->setText(delta3);

}

void MQSerial::on_comboBox_2_activated(int a)
{
    myCom->setBaudRate((BaudRateType)a);
    canshubiao[0]=a;
}

void MQSerial::on_comboBox_3_activated(int index)
{
    myCom->setDataBits((DataBitsType)index);
    canshubiao[1]=index;
}

void MQSerial::on_comboBox_5_activated(int index)
{
    myCom->setParity((ParityType)index);
    canshubiao[2]=index;
}

void MQSerial::on_comboBox_4_activated(int index)
{
    myCom->setStopBits((StopBitsType)index );
    canshubiao[3]=index;
}

void MQSerial::on_lineEdit_editingFinished()
{
   // myCom->write(ui->lineEdit->text().toAscii());
}

void MQSerial::on_lineEdit_textChanged(const QString &arg1)
{
    QString aa=arg1;
    if(ui->lineEdit->text().size()==0)
        ui->pushButton_3->setEnabled(false);
    else
        ui->pushButton_3->setEnabled(true);

}

void MQSerial::on_pushButton_8_clicked()
{
    ui->comboBox->clear();
    for(int i=0;comm.getcomm(i,"value")!="nokey";i++)
    {
      ui->comboBox->addItem(comm.getcomm(i,"value"));
    }

}

void MQSerial::on_pushButton_6_clicked()
{
    ui->plainTextEdit->moveCursor(QTextCursor::Start);
}

void MQSerial::on_pushButton_5_clicked()
{
    ui->plainTextEdit->clear();
    alltext.clear();
    receivenum=0;
    sendnum=0;
}

void MQSerial::on_checkBox_2_stateChanged(int arg1)
{
        //ŃĄÖĐÎŞ2
    ui->plainTextEdit->clear();
    int textsize=alltext.toLatin1().size();
    QString zhongjie=alltext.toLatin1().toHex();
    for(long i=0;i<textsize;i++)
        zhongjie.insert(3*i," ");
    if(arg1==2)
    ui->plainTextEdit->appendPlainText(zhongjie);
    else
        ui->plainTextEdit->appendPlainText(alltext);
    this->isAnimated();
}
//bool ishex(char a)
//{
//    if((a>='a'&&a<='f')||(a>='A'&&a<='F')||((a>='0')&&(a<='9')))
//        return true;
//    else return false;
//}





void MQSerial::on_checkBox_7_clicked()
{

}





void MQSerial::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr(""), ".", tr("all Files(*.*)"));
          if(path.length() == 0) {
                  QMessageBox::information(NULL, tr(""), tr(""));
          } else {
                  QMessageBox::information(NULL, tr(""), tr("~") + path);
          }
          QFile aa(path);
          if( aa.open(QIODevice::ReadOnly))
          {
         //   QTextStream textStream(&aa);
           // while(!textStream.atEnd())
           // {
             ui->plainTextEdit->appendPlainText(aa.readAll().toHex());
             if(!ui->checkBox_3->isChecked())
             {
                 QByteArray fasonghex=aa.readAll();

                 if(ui->checkBox_10->isChecked())
                 {
                     myCom->write(aa.readAll().append("\n"));

                 }
                 else
                 {
                     myCom->write(aa.readAll());

                 }
             }
             else
             {
                 QByteArray fasonghex=aa.read(1000000000);

                 QString fasongzhi;
                 int indexjishu=0;
                 QString fasongxinxi;
                 while(1)
                 {


                     if(indexjishu+1>=fasonghex.size())
                         break;
                     {

                         char a[3];
                         if(ishex(fasonghex[indexjishu]))
                         a[0]=fasonghex[indexjishu];
                         else
                         {
                             QString aa=tr(" ");
                             //cuowutishi->ui->label->setText(aa);
                             //cuowutishi->show();

                         break;
                         }
                         if(ishex(fasonghex[indexjishu+1]))
                         a[1]=fasonghex[indexjishu+1];
                         else
                         {
                             QString aa=tr(" ");
                             //cuowutishi->ui->label->setText(aa);
                             //cuowutishi->show();
                         break;
                         }
                         a[2]='\0';
                         QByteArray text = QByteArray::fromHex(a);
                         fasongxinxi.append(text.data());


                         if(fasonghex[indexjishu+2]==' ')
                         indexjishu+=3;
                         else
                         indexjishu+=2;


                     }
                 }
                 if(ui->checkBox_10->isChecked())
                 {
                     myCom->write(fasongxinxi.insert(0,"\n").toLatin1());

                 }
                 else
                 {
                     myCom->write(fasongxinxi.toLatin1());

                 }

             }

           // }

          }
        QString delta;
        sendnum+=ui->plainTextEdit->textCursor().position()/2;
        delta=QString("%1").arg(sendnum);
        ui->lineEdit_2->setText(delta);

          aa.close();

}

void MQSerial::on_pushButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr(""), ".", tr("all Files(*.*)"));
          if(path.length() == 0) {
                  QMessageBox::information(NULL, tr(""), tr(""));
          } else {
                  QMessageBox::information(NULL, tr(""), tr("~") + path);
          }
          QFile bb(path);
          if(bb.open(QIODevice::WriteOnly))
          {
            bb.write(ui->plainTextEdit->toPlainText().toLatin1());
          }
          bb.close();

}


void MQSerial::on_verticalSlider_sliderReleased()
{
    btm_state->setText(QString("%1").arg(this->ui->verticalSlider->value()));
}


void MQSerial::on_dial_sliderReleased()
{
    btm_state->setText(QString("%1").arg(this->ui->dial->value()));
}

