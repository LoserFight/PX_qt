QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += charts
QT       += serialport
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    callout.cpp \
    comsetdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    qchartviewplus.cpp \
    serialcom.cpp

HEADERS += \
    callout.h \
    comsetdialog.h \
    mainwindow.h \
    qchartviewplus.h \
    serialcom.h

FORMS += \
    comsetdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
