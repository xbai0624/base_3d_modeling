######################################################################
# Automatically generated by qmake (3.1) Mon Sep 5 14:05:36 2022
######################################################################

TEMPLATE = app
TARGET = main

INCLUDEPATH += ./include ./apv_mapping

QT += core gui widgets opengl
CONFIG += 
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS -= -std=gnu++1z

MOC_DIR = moc
OBJECTS_DIR = obj

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Main Input
HEADERS += \
           include/Module.h \
           include/Cube.h \
           include/OpenGLView.h \
           include/GeometryView.h \
           include/GeometryManager.h \
           include/GeometryBuilder.h \
           include/UnitTest.h \

SOURCES += \
           src/main.cpp \
           src/Module.cpp \
           src/Cube.cpp \
           src/OpenGLView.cpp \
           src/GeometryView.cpp \
           src/GeometryManager.cpp \
           src/GeometryBuilder.cpp \
           src/UnitTest.cpp \

# subsystem input
HEADERS += \
           apv_mapping/APVMapping.h \
           apv_mapping/APVStruct.h \

SOURCES += \
           apv_mapping/APVMapping.cpp \
           apv_mapping/APVStruct.cpp \