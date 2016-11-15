#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T19:32:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = generateimage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deal.c

HEADERS  += mainwindow.h \
    stb_image.h \
    stb_image_resize.h \
    stb_image_write.h

FORMS    += mainwindow.ui
