QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fondo.cpp \
    main.cpp \
    mainwindow.cpp \
    nivel1.cpp \
    obstaculo.cpp \
    personajebase.cpp \
    personajenivel1.cpp \
    personajenivel2.cpp

HEADERS += \
    fondo.h \
    mainwindow.h \
    nivel1.h \
    obstaculo.h \
    personajebase.h \
    personajenivel1.h \
    personajenivel2.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Imagenes.qrc
