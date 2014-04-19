#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T21:30:26
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtHaveModule(network))
TARGET = chuankou_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qextserialport.cpp \
    mqinternet.cpp \
    mqserial.cpp

HEADERS  += mainwindow.h \
    qextserialport.h \
    trash.h \
    tishi.h \
    mqinternet.h \
    mqserial.h

FORMS    += mainwindow.ui \
    mqinternet.ui
