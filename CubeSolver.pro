#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T01:07:17
#
#-------------------------------------------------

QT       += core gui
win32:RC_ICONS += icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CubeSolver
TEMPLATE = app

SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/pyra.cpp \
    Sources/scrambledialog.cpp \
    Sources/scrambledialog2x2.cpp \
    Sources/scrambledialogpyra.cpp \
    Sources/solver.cpp \
    Sources/solver2x2.cpp \
    Sources/solverpyra.cpp \
    Sources/solversq.cpp \
    Sources/sq1.cpp \
    Sources/tab2x2.cpp \
    Sources/tab3x3.cpp
HEADERS  += \
    Header/mainwindow.h \
    Header/pyra.h \
    Header/scrambledialog.h \
    Header/scrambledialog2x2.h \
    Header/scrambledialogpyra.h \
    Header/solver.h \
    Header/solver2x2.h \
    Header/solverpyra.h \
    Header/solversq.h \
    Header/sq1.h

FORMS    += \
    UI/mainwindow.ui \
    UI/scrambledialog.ui \
    UI/scrambledialog2x2.ui \
    UI/scrambledialogpyra.ui
