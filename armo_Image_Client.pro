QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../armo_Image/armoShowImageSK.cc \
        armo_client_global.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../armo_Image/armoShowImage.hh \
    armo_client_global.h
INCLUDEPATH += "e:\Soft\omniORB\omniORB-vs-15-4.2.4\include"
INCLUDEPATH += "c:\Users\Z\.nuget\packages\pthreads\2.9.1.4\build\native\include"
LIBS += "e:\Soft\omniORB\omniORB-vs-15-4.2.4\lib\x86_win32\omniORB424_rtd.lib"
LIBS += "e:\Soft\omniORB\omniORB-vs-15-4.2.4\lib\x86_win32\omnithread41_rtd.lib"
LIBS += "e:\Soft\omniORB\omniORB-vs-15-4.2.4\lib\x86_win32\omniDynamic424_rtd.lib"

DISTFILES += \
    README.txt
