QT += core
QT -= gui
TARGET = voceqt
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    place.cpp
INCLUDEPATH += "C:\voce-0.9.1\src\c++" "C:\Program Files\Java\jdk1.8.0_11\include" "C:\Program Files\Java\jdk1.8.0_11\include\win32"
LIBS += "-LC:\Program Files\Java\jdk1.8.0_11\jre\bin\server" "-LC:\Program Files\Java\jdk1.8.0_11\lib" -ljvm

DISTFILES += \
    lib/voce.config.xml \
    lib/digits.gram

HEADERS += \
    place.h
