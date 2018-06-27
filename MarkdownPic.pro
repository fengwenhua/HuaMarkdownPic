#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T00:09:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarkdownPic
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    accountdialog.cpp \
    renamedialog.cpp \
    globalsettingdialog.cpp

HEADERS += \
        mainwindow.h \
    debug.h \
    accountdialog.h \
    renamedialog.h \
    globalsettingdialog.h

FORMS += \
        mainwindow.ui \
    accountdialog.ui \
    renamedialog.ui \
    globalsettingdialog.ui






unix|win32: LIBS += -L$$PWD/lib/ -lcurllib

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -llibeay32

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lopenldap

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lqiniu

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lssleay32

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
