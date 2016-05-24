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


SOURCES += main.cpp\
        mainwindow.cpp \
    solver.cpp \
    scrambledialog.cpp \
    solver2x2.cpp \
    tab2x2.cpp \
    scrambledialog2x2.cpp \
    solverpyra.cpp \
    pyra.cpp \
    tab3x3.cpp \
    scrambledialogpyra.cpp \
    solversq.cpp \
    sq1.cpp

HEADERS  += mainwindow.h \
    solver.h \
    scrambledialog.h \
    solver2x2.h \
    scrambledialog2x2.h \
    solverpyra.h \
    pyra.h \
    scrambledialogpyra.h \
    solversq.h \
    sq1.h

FORMS    += mainwindow.ui \
    scrambledialog.ui \
    scrambledialog2x2.ui \
    scrambledialogpyra.ui
