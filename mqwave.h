#ifndef MQWAVE_H
#define MQWAVE_H

#include <QMainWindow>
#include <QList>
#include <QGraphicsScene>
#include <QDebug>
#include <QHBoxLayout>
#include <QPainter>
#include <QtOpenGL/qgl.h>
#include <QKeyEvent>
#include <GL/GLU.h>
//#include <GL/glaux.h>
#include <GL/gl.h>
#include <QtOpenGl/QtOpenGL>
namespace Ui {
class MQWave;
}

typedef long wave_type;


template <typename T>
class data_Line;


class miaoPainter : public QWidget
{
public :
    explicit miaoPainter(QList<data_Line<wave_type> > *line_list,wave_type max,wave_type min);
    void paintEvent(QPaintEvent *);
    QList<data_Line<wave_type> > *line_list;
    void resizeEvent(QResizeEvent *);
    wave_type max=1000;
    wave_type min=0;
    int busy_flag;
};

template <typename T>
class data_Line
{
public:
    data_Line(Qt::GlobalColor);
    void addData(T);
    void setColor(Qt::GlobalColor);
    void clear(void);

    QVector<T> data;
    Qt::GlobalColor color;
private:



};
class MQGl;

class MQWave : public QMainWindow
{
    Q_OBJECT

public:
    explicit MQWave(QWidget *parent = 0);
    Ui::MQWave *ui;

    ~MQWave();
    QGraphicsScene *scene;
    void setMax(wave_type);
    void setMin(wave_type);
    void addLine(long index,Qt::GlobalColor);
    void addData(long line_index,wave_type data);
    void pause();
    void clear();
    void start();
    MQGl *mqgl;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    QList<data_Line<wave_type> > line_list;
    miaoPainter *painter;
    QHBoxLayout *widget_layout;
    QHBoxLayout *widget_layout2;
    bool running_flag=1;



};


class MQGl : public QGLWidget
{
    Q_OBJECT

public:

    MQGl(QGLWidget *parent = 0);
    ~MQGl();
    GLfloat rTri;
    GLfloat rQuad;
    GLfloat rTri1;
    GLfloat rQuad1;
     void paintGL();
protected:
    void initializeGL();

    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
    bool fullscreen;


};



#endif // MQWAVE_H
