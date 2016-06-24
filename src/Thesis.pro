#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T21:47:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Thesis
TEMPLATE = app
QTPLUGIN += qico

SOURCES += main.cpp \
    MainWindow.cpp \
    MainSceneGL.cpp \
    Camera.cpp \
    Scene.cpp \
    SceneObject.cpp \
    Cube.cpp \
    Axes.cpp \
    SceneSettingsDialog.cpp \
    Sphere.cpp \
    Triangle.cpp \
    Spiral.cpp \
    Line.cpp \
    Bracket.cpp \
    Plane.cpp \
    SphereSettings.cpp \
    SceneObjectModel.cpp \
    CubeSettings.cpp \
    PlaneSettings.cpp \
    AxesSettings.cpp \
    BracketSettings.cpp \
    SpiralSettings.cpp \
    LineSettings.cpp \
    ./res/CsvParser/src/csvparser.c \
    Animator.cpp \
    AnimatorSphere.cpp \
    Animate.cpp


HEADERS  += MainWindow.h \
    MainSceneGL.h \
    Camera.h \
    Scene.h \
    SceneObject.h \
    Cube.h \
    Axes.h \
    SceneSettingsDialog.h \
    Sphere.h \
    Triangle.h \
    Spiral.h \
    Line.h \
    Bracket.h \
    Plane.h \
    SphereSettings.h \
    SceneObjectModel.h \
    CubeSettings.h \
    PlaneSettings.h \
    AxesSettings.h \
    BracketSettings.h \
    SpiralSettings.h \
    LineSettings.h \
    ./res/CsvParser/src/csvparser.h \
    Animator.h \
    AnimatorSphere.h \
    Animate.h

FORMS    += \
    MainWindow.ui \
    SceneSettingsDialog.ui \
    SphereSettings.ui \
    CubeSettings.ui \
    PlaneSettings.ui \
    AxesSettings.ui \
    BracketSettings.ui \
    SpiralSettings.ui \
    LineSettings.ui

INCLUDEPATH += $$PWD/'res/GLM'
INCLUDEPATH += $$PWD/'res'

DISTFILES += \
    shaders/cubeVertex.glsl \
    shaders/cubeFragment.glsl

DEFINES += DEBUG

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui

RESOURCES += \
    resourceFile.qrc

install_it.path = $$OUT_PWD
install_it.files = ./shaders/*.*
inst_it.path = $$DESTDIR 
inst_it.files = ./shaders/*.*
INSTALLS += \
    install_it\
	inst_it
