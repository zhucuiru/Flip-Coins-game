#-------------------------------------------------
#
# Project created by QtCreator 2020-05-28T20:47:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 031_Flip_Coins
TEMPLATE = app


SOURCES += main.cpp\
        mainsense.cpp \
    mypushbutton.cpp \
    chooselevelsence.cpp \
    playscense.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS  += mainsense.h \
    mypushbutton.h \
    chooselevelsence.h \
    playscense.h \
    mycoin.h \
    dataconfig.h

FORMS    += mainsense.ui

RESOURCES += \
    res.qrc
