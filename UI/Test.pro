QT       += core gui
LIBS +=/usr/include/boost/functional/hash.hpp
LIBS +=/usr/include/boost/regex.hpp
LIBS +=/usr/include/boost/algorithm/string.hpp

DEFINES +=BOOST_USE_LIB

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp \
    algorithms/svp_plus.cpp \
    model/graph.cpp \
    tools/tools.cpp

HEADERS += \
    widget.h \
    algorithms/kspwlo.hpp \
    model/graph.hpp \
    tools/tools.hpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
