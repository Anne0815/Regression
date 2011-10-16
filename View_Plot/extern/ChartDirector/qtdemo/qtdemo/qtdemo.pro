# -------------------------------------------------
# QT Project File
# -------------------------------------------------
TARGET = qtdemo

TEMPLATE = app

SOURCES += qchartviewer.cpp \
    hotspotdialog.cpp \
    qtdemo.cpp \
    democharts.cpp
    
HEADERS += qchartviewer.h \
    hotspotdialog.h \
    qtdemo.h \
    democharts.h

INCLUDEPATH += ../../include

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS

win32:DESTDIR = $$PWD
win32:LIBS += ../../lib/chartdir50.lib
win32:QMAKE_POST_LINK += copy /Y ..\..\lib\chartdir50.dll

macx:CONFIG -= app_bundle
macx:DESTDIR = $$PWD
macx:LIBS += -L../../lib -lchartdir
macx:QMAKE_POST_LINK += cp ../../lib/libchartdir.5.dylib \"$(DESTDIR)\"

unix:!macx:DESTDIR = $$PWD
unix:!macx:LIBS += -L../../lib -lchartdir
unix:!macx:QMAKE_RPATHDIR += ../../lib

