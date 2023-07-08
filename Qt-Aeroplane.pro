QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Game.cpp \
    QPlane.cpp \
    gen_.cpp \
    main.cpp \
    mainwindow.cpp \
    mousehover.cpp \
    plane.cpp \
    prop.cpp \
    qrimage.cpp \
    square.cpp \
    start.cpp \
    structures.cpp \
    win.cpp

HEADERS += \
    Game.h \
    QPlane.h \
    gen_.h \
    mainwindow.h \
    mousehover.h \
    path.h \
    plane.h \
    prop.h \
    qrimage.h \
    square.h \
    start.h \
    structures.h \
    win.h

FORMS += \
    mainwindow.ui \
    prop.ui \
    qrimage.ui \
    start.ui \
    win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Bgm.py
