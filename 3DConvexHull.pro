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


SOURCES += main.cpp \
    topologicds.cpp \
    utils.cpp \
    convexhull2d.cpp

win32 {
    INCLUDEPATH += "$(CG_INC_PATH)" \
        "$(OPENCV_INCLUDE_DIR)"

    CONFIG(debug,debug|release) {
        LIBS += -L"$(CG_LIB64_PATH)" \
            -lglut32 \
            -L"$(OPENCV_LIB_DIR)" \
            -lopencv_core$(OPENCV_VERSION)d \
            -lopencv_highgui$(OPENCV_VERSION)d \
            -lopencv_imgproc$(OPENCV_VERSION)d \
            -lopencv_features2d$(OPENCV_VERSION)d \
            -lopencv_calib3d$(OPENCV_VERSION)d \
            -lopencv_contrib$(OPENCV_VERSION)d
    }

    CONFIG(release,debug|release) {
        DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
        LIBS += -L"$(CG_LIB64_PATH)" \
            -lglut32 \
            -L"$(OPENCV_LIB_DIR)" \
            -lopencv_core$(OPENCV_VERSION) \
            -lopencv_highgui$(OPENCV_VERSION) \
            -lopencv_imgproc$(OPENCV_VERSION) \
            -lopencv_features2d$(OPENCV_VERSION) \
            -lopencv_calib3d$(OPENCV_VERSION) \
            -lopencv_contrib$(OPENCV_VERSION)
    }
}

HEADERS +=
