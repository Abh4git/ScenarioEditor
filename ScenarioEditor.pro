# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = ScenarioEditor
DESTDIR = ./Output
QT += widgets
#core gui
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT QT_DLL
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
#LIBS += C:\Abhilash\MyToolBox\OpenSourceBranch\ScenarioEditor\Output\libBOMLibrary.a
LIBS += $$PWD/Output/libBOMLibrary.a
LIBS += $$PWD/Output/libBOMGraphicalLibrary.a
    #-l BOMLibrary \
    #-l BOMGraphicalLibrary
#MAKEFILE = Makefile
#PRECOMPILED_HEADER = StdAfx.h
DEPENDPATH += ./Output
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
RESOURCES += ./Resources/automationwizard.qrc
include(ScenarioEditor.pri)