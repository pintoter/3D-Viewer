QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_affine.c \
    ../s21_converter.c \
    ../s21_loader.c \
    ../s21_remove.c \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp

HEADERS += \
    ../include/s21_3DViewer_v1.h \
    ../include/s21_matrix.h \
    mainwindow.h \
    myopenglwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += ../include/libs21_matrix.a
include(QtGifImage/src/gifimage/qtgifimage.pri)
