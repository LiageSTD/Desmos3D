QT       += core gui widgets datavisualization

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    plot.cpp

HEADERS += \
    mainwindow.h \
    plot.h

TRANSLATIONS += \
    Language_CN.ts \
    Language_ENG.ts \
    Language_EM.ts
CONFIG += lrelease
CONFIG += embed_translations

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Language_CN.ts \
    Language_en_GB.ts \
    Language_EM.ts \
    cat.jpg

win32:RC_FILE = file.rc
