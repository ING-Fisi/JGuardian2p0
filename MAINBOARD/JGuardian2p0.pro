TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += LINUX

CONFIG += c++14

//**************************************

DEFINES += DEV3


///***********************************

SOURCES += \
    Analog.cpp \
    JGuardian.cpp \
    Logger.cpp \
    command.cpp \
    gpio.cpp


# Default rules for deployment.
qnx: target.path = /home/fisitron/$${TARGET}/bin
else: unix:!android: target.path = /home/fisitron/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += -lssl
LIBS += -lcrypto
LIBS += -lgpiod
LIBS += -lcurl


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LIBRERIE_STM32MP1/paho_mqtt_c/build/src/release/ -lpaho-mqtt3as
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LIBRERIE_STM32MP1/paho_mqtt_c/build/src/debug/ -lpaho-mqtt3as
else:unix: LIBS += -L$$PWD/../../LIBRERIE_STM32MP1/paho_mqtt_c/build/src/ -lpaho-mqtt3as

INCLUDEPATH += $$PWD/../../LIBRERIE_STM32MP1/paho_mqtt_c/src
DEPENDPATH += $$PWD/../../LIBRERIE_STM32MP1/paho_mqtt_c/src





HEADERS += \
    Analog.h \
    JGuardian.h \
    Logger.h \
    command.h \
    gpio.h




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/LIB/release/ -ljwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/LIB/debug/ -ljwt
else:unix: LIBS += -L$$PWD/LIB/ -ljwt

INCLUDEPATH += $$PWD/../../../LIBRERIE_STM32MP1/JWT/jwt-cpp/src/include
DEPENDPATH += $$PWD/../../../LIBRERIE_STM32MP1/JWT/jwt-cpp/src/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/LIB/release/libjwt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/LIB/debug/libjwt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/LIB/release/jwt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/LIB/debug/jwt.lib
else:unix: PRE_TARGETDEPS += $$PWD/LIB/libjwt.a




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/LIB/release/ -lmodbus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/LIB/debug/ -lmodbus
else:unix: LIBS += -L$$PWD/LIB/ -lmodbus

INCLUDEPATH += $$PWD/../../../LIBRERIE_STM32MP1/libmodbus/src
DEPENDPATH += $$PWD/../../../LIBRERIE_STM32MP1/libmodbus/src

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/LIB/release/ -lpaho-mqtt3as
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/LIB/debug/ -lpaho-mqtt3as
else:unix: LIBS += -L$$PWD/LIB/ -lpaho-mqtt3as

INCLUDEPATH += $$PWD/../../../LIBRERIE_STM32MP1/paho_mqtt_c/src
DEPENDPATH += $$PWD/../../../LIBRERIE_STM32MP1/paho_mqtt_c/src
