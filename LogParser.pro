#-------------------------------------------------
#
# Project created by QtCreator 2020-02-10T10:01:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogParser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#RC_ICONS = bosch_S3O_icon.ico

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    directoryops.cpp \
    logoperations.cpp \
    xmlparser.cpp \
    logger.cpp

HEADERS += \
        mainwindow.h \
    directoryops.h \
    definitions.h \
    logoperations.h \
    xmlparser.h \
    logger.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    images.qrc


