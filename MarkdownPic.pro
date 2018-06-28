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





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lqiniu
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lqiniu
else:unix: LIBS += -L$$PWD/./ -lqiniu

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/libqiniu.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/libqiniu.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/qiniu.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/qiniu.lib
else:unix: PRE_TARGETDEPS += $$PWD/./libqiniu.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lqiniu
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lqiniu
else:unix: LIBS += -L$$PWD/./ -lqiniu

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
