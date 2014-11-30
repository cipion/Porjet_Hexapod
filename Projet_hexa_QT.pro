#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T08:21:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Projet_hexa_QT
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    hexapod/hexapod.cpp \
    robot/Patte.cpp \
    robot/Robot.cpp \
    servomoteur/AX12.cpp \
    servomoteur/ServoMoteur.cpp \
    stdrpi/SerialRPi.cpp

HEADERS += \
    hexapod/hexapod.h \
    robot/Patte.h \
    robot/Robot.h \
    servomoteur/AX12.h \
    servomoteur/ServoMoteur.h \
    stdrpi/SerialRPi.h