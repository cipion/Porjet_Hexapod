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


SOURCES += \
    hexapod/hexapod.cpp \
    robot/Patte.cpp \
    robot/Robot.cpp \
    servomoteur/AX12.cpp \
    servomoteur/ServoMoteur.cpp \
    stdrpi/SerialRPi.cpp \
    robot/StructPatte.cpp \
    robot/PeriodicUpdateTask.cpp \
    jetty/robotwebsockethandler.cpp \
    jetty/websocketrobot.cpp

HEADERS += \
    robot/Patte.h \
    robot/Robot.h \
    servomoteur/AX12.h \
    servomoteur/ServoMoteur.h \
    stdrpi/SerialRPi.h \
    robot/StructPatte.h \
    robot/PeriodicUpdateTask.h \
    jetty/robotwebsockethandler.h \
    jetty/websocketrobot.h

OTHER_FILES += \
    README.txt \
    Etat_du_programme.txt
