######################################################################
# Automatically generated by qmake
# > qmake.exe -project
######################################################################

TEMPLATE = app
TARGET   = StreamWidget
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++11

gcc|clang{
    QMAKE_CFLAGS += -std=c99
    QMAKE_CXXFLAGS += -std=c++11
}

lessThan(QT_VERSION, 5.0) {
    warning("prefere to build it with Qt 5.0")
}


#-------------------------------------------------
# Dependencies
#-------------------------------------------------
HEADERS += \
    $$PWD/../../../src/core/format.h \
    $$PWD/../../../src/core/stream.h \
    $$PWD/../../../src/widgets/customstyle.h \
    $$PWD/../../../src/widgets/customstyleoptionprogressbar.h \
    $$PWD/../../../src/widgets/streamwidget.h

SOURCES += \
    $$PWD/../../../src/core/format.cpp \
    $$PWD/../../../src/core/stream.cpp \
    $$PWD/../../../src/widgets/customstyle.cpp \
    $$PWD/../../../src/widgets/customstyleoptionprogressbar.cpp \
    $$PWD/../../../src/widgets/streamwidget.cpp

FORMS += \
    $$PWD/../../../src/widgets/streamwidget.ui


#-------------------------------------------------
# INCLUDE
#-------------------------------------------------
INCLUDEPATH += $$PWD/../../../include/


#-------------------------------------------------
# SOURCES
#-------------------------------------------------
HEADERS += \
    $$PWD/mainwindow.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/main.cpp

FORMS += \
    $$PWD/mainwindow.ui


#-------------------------------------------------
# RESOURCES
#-------------------------------------------------
RESOURCES += $$PWD/../../../src/resources.qrc

win32|unix {
    RC_FILE += $$PWD/../../../src/resources_win.rc
}


#-------------------------------------------------
# BUILD OPTIONS
#-------------------------------------------------

# Rem: On Ubuntu, directories starting with '.' are hidden by default
win32{
    MOC_DIR =      ./.moc
    OBJECTS_DIR =  ./.obj
    UI_DIR =       ./.ui
}else{
    MOC_DIR =      ./_moc
    OBJECTS_DIR =  ./_obj
    UI_DIR =       ./_ui
}

#-------------------------------------------------
# OUTPUT
#-------------------------------------------------


#-------------------------------------------------
# TARGET DIRECTORY
#-------------------------------------------------
# Needs to define a subfolder, as the *.DLL
# cannot be copied in the root folder.
DESTDIR = $${OUT_PWD}/../../../manual_test_install


#-------------------------------------------------
# INSTALL
#-------------------------------------------------
# Remark:
# =======
# Eventually, in your favorite IDE, replace build chain command
#   'make'
# by
#   'make install'
#
# It will install the DLLs, documentation, data, etc.
# that are required to execute the application.
#

# instructions for 'make install'

# install Qt binaries (for Windows only)
# This is a hack for 'windeployqt'
win32{
    CONFIG(debug,debug|release){
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qminimald.dll
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qwindowsd.dll
        libs_qt_to_copy.path = $${DESTDIR}/platforms
        INSTALLS += libs_qt_to_copy
    }else{
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qminimal.dll
        libs_qt_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qwindows.dll
        libs_qt_to_copy.path = $${DESTDIR}/platforms
        INSTALLS += libs_qt_to_copy
    }
}

# install youtube-dl (for Windows only)
win32{
    youtube_dl_executable_to_copy.files += $$PWD/../../../3rd/youtube-dl/v2020.01.01/youtube-dl.exe
    youtube_dl_executable_to_copy.path = $${DESTDIR}
    INSTALLS += youtube_dl_executable_to_copy
}
