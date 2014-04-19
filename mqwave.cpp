#include "mqwave.h"
#include "ui_mqwave.h"
MQGl::MQGl(QGLWidget *parent )
    : QGLWidget( parent)
{
    fullscreen=false;
    setGeometry(0,0,this->width(),this->height());

    rTri=0;
    rQuad=0;
}
MQGl::~MQGl()
{

}
void MQGl::initializeGL()
{
    //setGeometry(300, 150, 640, 480);//设置窗口初始位置和大小
    glShadeModel(GL_SMOOTH);//设置阴影平滑模式
    glClearColor(0.7, 0.3, 1, 0);//改变窗口的背景颜色，不过我这里貌似设置后并没有什么效果
    glClearDepth(1.0);//设置深度缓存
    glEnable(GL_DEPTH_TEST);//允许深度测试
    glDepthFunc(GL_LEQUAL);//设置深度测试类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正
}
void MQGl::paintGL()
{
    //glClear()函数在这里就是对initializeGL()函数中设置的颜色和缓存深度等起作用
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//重置当前的模型观察矩阵？不是很理解！

    glTranslatef( -1.5,  0.0, -6.0 );
//    glRotatef( rTri,  0.0,  1.0,  0.0 );
//    glRotatef( rQuad,  1.0,  0.0,  0.0 );
//    glBegin( GL_TRIANGLES );
//    glColor3f( 1.0, 0.0, 0.0 );
//    glVertex3f(  0.0,  1.0,  0.0 );
//    glColor3f( 1.0, 0.0, 1.0 );
//    glVertex3f( -1.0, -1.0,  0.0 );
//    glColor3f( 0.0, 1.0, 0.0 );
//    glVertex3f(  1.0, -1.0,  0.0 );
//    glEnd();
    //glLoadIdentity();
//    glRotatef( -rQuad,  1.0,  0.0,  0.0 );
//    glRotatef( -rTri,  0.0,  1.0,  0.0 );
    glTranslatef(  3,  0.0, 0 );
    glRotatef( rQuad,  1.0,  0.0,  0.0 );
    glRotatef( rTri,  0.0,  0.0,  1.0 );
    glBegin( GL_QUADS );

    glColor3f( 1.0, 1.0, 0.0 );
    glVertex3f( -1.0,  1.0,  0.0 );

    glColor3f( 0.0, 1, 0.0 );
    glVertex3f(  1.0,  1.0,  0.0 );

    glColor3f( 0.0, 1,1 );
    glVertex3f(  1.0, -1.0,  0.0 );

    glColor3f( 1.0, 0.0, 1 );
    glVertex3f( -1.0, -1.0,  0.0 );

    glEnd();
    glRotatef( -rQuad,  1.0,  0.0,  0.0 );
    glLoadIdentity();


}
void MQGl::resizeGL(int width, int height)
{
    if(0 == height)
        height = 1;//防止一条边为0
    glViewport(0, 0, (GLint)width, (GLint)height);//重置当前视口，本身不是重置窗口的，只不过是这里被Qt给封装好了
    glMatrixMode(GL_PROJECTION);//选择投影矩阵
    glLoadIdentity();//重置选择好的投影矩阵
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);//建立透视投影矩阵
    glMatrixMode(GL_MODELVIEW);//以下2句和上面出现的解释一样
    glLoadIdentity();


}
void MQGl::keyPressEvent(QKeyEvent *ess)
{
    switch(ess->key())
    {
        //F1键为全屏和普通屏显示切换键
        case Qt::Key_F1:
            fullscreen = !fullscreen;
            if(fullscreen)
                showFullScreen();
            else
            {
                setGeometry(300, 150, 640, 480);
                showNormal();
            }
            updateGL();
            break;
        //Ese为退出程序键
        case Qt::Key_Escape:
            close();
    }
}

MQWave::MQWave(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MQWave)
{
    ui->setupUi(this);
    this->menuBar()->hide();
    this->statusBar()->hide();
    this->widget_layout=new QHBoxLayout();
    this->widget_layout2=new QHBoxLayout();

    this->mqgl=new MQGl();
    this->painter=new miaoPainter(&this->line_list,255,0);
    this->widget_layout->addWidget(this->painter);
    this->widget_layout2->addWidget(this->mqgl);
    ui->widget->setLayout(this->widget_layout);
    ui->widget_2->setLayout(this->widget_layout2);

    this->painter->busy_flag=0;



}

miaoPainter::miaoPainter(QList<data_Line<wave_type> > *line_list,wave_type max,wave_type min)
{
    this->line_list=line_list;
    this->max=max;
    this->min=min;
}
void miaoPainter::paintEvent(QPaintEvent *)
{
    this->busy_flag=1;
    QPainter ppp(this);

    QRectF waikuang(0,0,this->width(),this->height());
    ppp.fillRect(waikuang,Qt::black);


    for(int j=0;j<this->line_list->length();j++)
    {
        ppp.setPen(this->line_list->at(j).color);
        const QVector<wave_type> *data=&(this->line_list->at(j).data);
        int lenth=this->line_list->at(j).data.length();
        if(lenth<=this->width())
        {
            for(long i=0;i<lenth-1;i++)
            {
                wave_type data_left=((this->max-(*data)[i])*this->height()/(max-min));
                wave_type data_right=((this->max-(*data)[i+1])*this->height()/(max-min));
                ppp.drawLine(i,data_left,i+1,data_right);
            }
        }
        else
        {
            for(long i=lenth-this->width();i<lenth-1;i++)
            {
                wave_type data_left=((this->max-(*data)[i])*this->height()/(max-min));
                wave_type data_right=((this->max-(*data)[i+1])*this->height()/(max-min));
                ppp.drawLine(i-(lenth-this->width()),data_left,i+1-(lenth-this->width()),data_right);

            }
        }

    }
    this->busy_flag=0;

}
void miaoPainter::resizeEvent(QResizeEvent *)
{
    //    qDebug()<<this->width();
    this->repaint();
}
void MQWave::setMax(wave_type max)
{
    this->painter->max=max;
}

void MQWave::setMin(wave_type min)
{
    this->painter->min=min;
}

MQWave::~MQWave()
{
    delete ui;
}

void MQWave::addLine(long index,Qt::GlobalColor color)
{
    index=index;
    data_Line<wave_type>* line=new data_Line<wave_type>(color);
    this->line_list.append(*line);
    delete(line);
}

void MQWave::addData(long line_index,wave_type data)
{

    //this->line_list.at(line_index).addData(data);
    if(!running_flag)
        return ;
    if(data>this->painter->max)
        data=this->painter->max;
    else if(data<this->painter->min)
        data=this->painter->min;

    this->line_list[line_index].addData(data);
    if(!this->painter->busy_flag)
        ui->widget->update();
}





template <typename T>
void data_Line<T>::addData(T data)
{
    this->data.append(data);
}
template <typename T>
void data_Line<T>::clear()
{
    this->data.clear();
    //this->color=Qt::white;

}
template <typename T>
data_Line<T>::data_Line(Qt::GlobalColor color)
{
    this->color=color;
}

void MQWave::on_pushButton_clicked()
{
    if(running_flag)
    {
        pause();
        ui->pushButton->setText("Start");
    }
    else
    {
        start();
        ui->pushButton->setText("Pause");
    }

}
void MQWave::pause()
{
    running_flag=0;
}
void MQWave::start()
{
    running_flag=1;
}
void MQWave::clear()
{
    for(long i=0;i<this->line_list.length();i++)
        this->line_list[i].clear();
    ui->widget->update();
}

void MQWave::on_pushButton_2_clicked()
{
    this->clear();
}
