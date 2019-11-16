######################################################################
# Automatically generated by qmake
# > qmake.exe -project
######################################################################

TEMPLATE = app
TARGET   = DownZemAll
QT       += core gui
QT       += network

unix|win32-msvc* {
    QT   += webenginewidgets
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
include($$PWD/../3rd/3rd.pri)


#-------------------------------------------------
# Other
#-------------------------------------------------
win32{
    # Link to system library "version.dll" on Windows
    # Required by GetFileVersionInfo(), GetFileVersionInfoSize() and VerQueryValue()
    LIBS += -lVersion
}else{

}

win32-msvc* {
    # Build with QtWebEngine (Rem: works only with MSVC on Windows)
    DEFINES += USE_QT_WEBENGINE
}
unix{
    DEFINES += USE_QT_WEBENGINE
}

#-------------------------------------------------
# VERSION
#-------------------------------------------------
VERSION_FILENAME = $$PWD/../version

!exists( $${VERSION_FILENAME} ) {
    error( "Cannot find version file \"$${VERSION_FILENAME}\"" )
}

APP_VERSION = "$$cat($$VERSION_FILENAME)"
DEFINES += APP_VERSION=\\\"$$APP_VERSION\\\"


#-------------------------------------------------
# INCLUDE
#-------------------------------------------------
INCLUDEPATH += $$PWD/../include/


#-------------------------------------------------
# SOURCES
#-------------------------------------------------
include($$PWD/core/core.pri)
include($$PWD/dialogs/dialogs.pri)
include($$PWD/io/io.pri)
include($$PWD/widgets/widgets.pri)

HEADERS += \
    $$PWD/about.h \
    $$PWD/builddefs.h \
    $$PWD/globals.h \
    $$PWD/mainwindow.h \
    $$PWD/version.h


SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/main.cpp

FORMS += \
    $$PWD/mainwindow.ui



#-------------------------------------------------
# RESOURCES
#-------------------------------------------------
RESOURCES += $$PWD/resources.qrc

win32|unix {
    RC_FILE += $$PWD/resources_win.rc
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
DESTDIR = $${OUT_PWD}/../downzemall_install

#build_pass:CONFIG(debug, debug|release) {
#    unix: TARGET = $$join(TARGET,,,_debug)
#    else: TARGET = $$join(TARGET,,,d)
#}
#

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

# install OpenSSL (for Windows only)
win32{
    contains(QT_ARCH, i386) {
        # message("32-bit")
        #libs_openssl_to_copy.files += $$PWD/../3rd/openssl/v1.1.1/windows_x86_32bits/libcrypto-1_1.dll
        #libs_openssl_to_copy.files += $$PWD/../3rd/openssl/v1.1.1/windows_x86_32bits/libssl-1_1.dll
        libs_openssl_to_copy.files += $$PWD/../3rd/openssl/v1.0.2/windows_x86_32bits/libeay32.dll
        libs_openssl_to_copy.files += $$PWD/../3rd/openssl/v1.0.2/windows_x86_32bits/ssleay32.dll

    } else {
        # message("64-bit")
        libs_openssl_to_copy.files += $$PWD/../3rd/openssl/v1.1.1/windows_x86_64bits/libcrypto-1_1-x64.dll
        libs_openssl_to_copy.files += $$PWD/../3rd/openssl/v1.1.1/windows_x86_64bits/libssl-1_1-x64.dll
    }
    libs_openssl_to_copy.path = $${DESTDIR}
    INSTALLS += libs_openssl_to_copy
}

