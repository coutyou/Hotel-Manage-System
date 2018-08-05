#-------------------------------------------------
#
# Project created by QtCreator 2018-07-16T10:24:05
#
#-------------------------------------------------

QT += core gui
QT += core gui sql
CONFIG += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotelManageSystem
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
    login.cpp \
    hotelRegister.cpp \
    cusRegister.cpp \
    databasesl.cpp \
    mainwindowforhotellogin.cpp \
    hotel.cpp \
    room.cpp \
    order.cpp \
    people.cpp \
    peopleinfochange.cpp \
    hotelinfochange.cpp \
    hotelsearch.cpp \
    roomsearch.cpp \
    addorder.cpp \
    cancelorder.cpp \
    evaluation.cpp \
    updateorder.cpp \
    orderpay.cpp \
    mainwindowforplatformmanager.cpp \
    checkhotel.cpp \
    showimage.cpp

HEADERS += \
        mainwindow.h \
    login.h \
    cusRegister.h \
    databasesl.h \
    mainwindowforhotellogin.h \
    hotelRegister.h \
    hotel.h \
    room.h \
    log.h \
    order.h \
    people.h \
    peopleinfochange.h \
    hotelinfochange.h \
    hotelsearch.h \
    roomsearch.h \
    addorder.h \
    cancelorder.h \
    evaluation.h \
    updateorder.h \
    orderpay.h \
    mainwindowforplatformmanager.h \
    checkhotel.h \
    showimage.h

FORMS += \
        mainwindow.ui \
    login.ui \
    hotelRegister.ui \
    cusregister.ui \
    mainwindowforhotellogin.ui \
    peopleinfochange.ui \
    hotelinfochange.ui \
    hotelsearch.ui \
    roomsearch.ui \
    addorder.ui \
    cancelorder.ui \
    evaluation.ui \
    updateorder.ui \
    orderpay.ui \
    mainwindowforplatformmanager.ui \
    checkhotel.ui \
    showimage.ui

RESOURCES += \
    icon.qrc

DISTFILES +=
