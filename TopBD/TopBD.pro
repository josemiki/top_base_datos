#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T09:15:40
#
#-------------------------------------------------

QT       += core gui
#Intall sudo apt-get install libqt5webkit5-dev
QT += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TopBD
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += c++11
