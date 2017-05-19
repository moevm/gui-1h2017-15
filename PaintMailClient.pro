#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T21:19:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintMailClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        loginwindow.cpp \
    abstractconnectionmanager.cpp \
    connectionlistener.cpp \
    smtpconnectionmanager.cpp \
    message.cpp \
    mailbox.cpp \
    Pop3Client.cpp \
    myparser.cpp \
    sendmessage.cpp \
    msgbody.cpp

HEADERS  += loginwindow.h \
    abstractconnectionmanager.h \
    address.h \
    connectionlistener.h \
    smtpconnectionmanager.h \
    message.h \
    mailbox.h \
    Pop3Client.h \
    myparser.h \
    sendmessage.h \
    msgbody.h

FORMS    += loginwindow.ui\
            mailbox.ui \
    sendmessage.ui


QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    image.qrc\
    msg6.txt
