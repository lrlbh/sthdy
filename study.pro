QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app_data.cpp \
    laozi.cpp \
    main.cpp \
    mainwindow.cpp \
    zhouyi.cpp

HEADERS += \
    app_data.h \
    laozi.h \
    mainwindow.h \
    zhouyi.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    xml/AndroidManifest.xml

RESOURCES += \
    res.qrc

#隐藏状态栏
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/xml

#android{
#langs.files += img/*.jpg
#langs.path = /assets/Language
#INSTALLS += langs
#}

#contains(ANDROID_TARGET_ARCH,arm64-v8a) {
#    ANDROID_PACKAGE_SOURCE_DIR = \
#        $$PWD/android
#}
