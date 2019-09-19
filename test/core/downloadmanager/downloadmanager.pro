#isEmpty(TEMPLATE):TEMPLATE=app
TARGET       = tst_downloadmanager
CONFIG      += testcase
QT           = core testlib network

SOURCES     += tst_downloadmanager.cpp

# Include:
INCLUDEPATH += ../../../include

# Resources:
HEADERS     += $$PWD/../../../src/core/downloadmanager.h
SOURCES     += $$PWD/../../../src/core/downloadmanager.cpp

HEADERS     += $$PWD/../../../src/core/downloaditem.h
SOURCES     += $$PWD/../../../src/core/downloaditem.cpp

HEADERS     += $$PWD/../../../src/core/resourceitem.h
SOURCES     += $$PWD/../../../src/core/resourceitem.cpp

HEADERS     += $$PWD/../../../src/core/mask.h
SOURCES     += $$PWD/../../../src/core/mask.cpp

HEADERS     += $$PWD/../../../src/core/session.h
SOURCES     += $$PWD/../../../src/core/session.cpp

HEADERS     += $$PWD/../../../src/core/settings.h
SOURCES     += $$PWD/../../../src/core/settings.cpp