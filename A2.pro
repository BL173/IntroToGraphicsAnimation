QT       += core gui opengl

TARGET = A2
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp \
    objects.cpp \
    PPMImage.cpp \
    RGBValue.cpp \
    quat.cpp \
    arcBall.cpp \
    vector.cpp \
    point.cpp


HEADERS  += mainwindow.h \
    glwidget.h \
    objects.h \
    PPMImage.h \
    RGBValue.h \
    quat.h \
    arcBall.h \
    vector.h \
    point.h

FORMS    += mainwindow.ui

RESOURCES += resources.qrc

win32: LIBS += -lopengl32
