#-------------------------------------------------
#
# Project created by QtCreator 2015-05-29T11:41:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = 3DConvexHull
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32 {
    INCLUDEPATH += "$(CG_INC_PATH)" \

    CONFIG(debug,debug|release) {
        LIBS += -L"$(CG_LIB64_PATH)" \
            -lglut32
    }

    CONFIG(release,debug|release) {
        DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
        LIBS += -L"$(CG_LIB64_PATH)" \
            -lglut32
    }
}
