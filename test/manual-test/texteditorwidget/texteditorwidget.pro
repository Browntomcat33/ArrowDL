######################################################################
# Automatically generated by qmake
# > qmake.exe -project
######################################################################

TEMPLATE = app
TARGET   = TexteEditorDemo
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
    $$PWD/../../../src/widgets/textedit.h \
    $$PWD/../../../src/widgets/texteditorwidget.h

SOURCES += \
    $$PWD/../../../src/widgets/textedit.cpp \
    $$PWD/../../../src/widgets/texteditorwidget.cpp

FORMS += \
    $$PWD/../../../src/widgets/texteditorwidget.ui


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
        platform_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qminimald.dll
        platform_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qwindowsd.dll
        platform_plugin_to_copy.path = $${DESTDIR}/platforms
        INSTALLS += platform_plugin_to_copy

        imageformats_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/imageformats/qgifd.dll
        imageformats_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/imageformats/qicod.dll
        imageformats_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/imageformats/qjpegd.dll
        imageformats_plugin_to_copy.path = $${DESTDIR}/imageformats
        INSTALLS += imageformats_plugin_to_copy

        style_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/styles/qwindowsvistastyled.dll
        style_plugin_to_copy.path = $${DESTDIR}/styles
        INSTALLS += style_plugin_to_copy
    }else{
        platform_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qminimal.dll
        platform_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/platforms/qwindows.dll
        platform_plugin_to_copy.path = $${DESTDIR}/platforms
        INSTALLS += platform_plugin_to_copy

        imageformats_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/imageformats/qgif.dll
        imageformats_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/imageformats/qico.dll
        imageformats_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/imageformats/qjpeg.dll
        imageformats_plugin_to_copy.path = $${DESTDIR}/imageformats
        INSTALLS += imageformats_plugin_to_copy

        style_plugin_to_copy.files += $$[QT_INSTALL_PLUGINS]/styles/qwindowsvistastyle.dll
        style_plugin_to_copy.path = $${DESTDIR}/styles
        INSTALLS += style_plugin_to_copy
    }
}
