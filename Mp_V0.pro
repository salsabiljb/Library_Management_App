#-------------------------------------------------
#
# Project created by QtCreator 2024-01-23T15:58:08
#
#-------------------------------------------------

QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Mp_V0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    admin_dialog.cpp \
    user_dialog.cpp \
    DBConnexion.cpp \
    Livre.cpp \
    adherents.cpp \
    adherentsdialog.cpp \
    emprunts_dialog.cpp \
    emprunts.cpp \
    livre_dialog.cpp \
    stat_dialog.cpp \
    histogramwidget.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    admin_dialog.h \
    user_dialog.h \
    DBConnexion.h \
    Livre.h \
    adherents.h \
    adherentsdialog.h \
    emprunts_dialog.h \
    emprunts.h \
    livre_dialog.h \
    stat_dialog.h \
    histogramwidget.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    admin_dialog.ui \
    user_dialog.ui \
    adherentsdialog.ui \
    emprunts_dialog.ui \
    livre_dialog.ui \
    stat_dialog.ui

RESOURCES += \
    resources.qrc \
    res.qrc
