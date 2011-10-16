# -------------------------------------------------
# QT Project File
# -------------------------------------------------
TARGET = financedemo

TEMPLATE = app

SOURCES += qchartviewer.cpp \
    hotspotdialog.cpp \
    financedemo.cpp
    
HEADERS += qchartviewer.h \
    hotspotdialog.h \
    financedemo.h

INCLUDEPATH += ../../include

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS

win32:LIBS += ../../lib/chartdir50.lib
win32:QMAKE_POST_LINK = copy /Y ..\..\lib\chartdir50.dll $(DESTDIR)

macx:LIBS += -L../../lib -lchartdir
macx:QMAKE_POST_LINK += mkdir -p \"`dirname $(TARGET)`/../Frameworks\";
macx:QMAKE_POST_LINK += cp ../../lib/libchartdir.5.dylib \"`dirname $(TARGET)`/../Frameworks\";
macx:QMAKE_POST_LINK += install_name_tool -change libchartdir.5.dylib \
     \@loader_path/../Frameworks/libchartdir.5.dylib \"$(TARGET)\";

unix:!macx:LIBS += -L../../lib -lchartdir
unix:!macx:QMAKE_RPATHDIR += ../../lib


