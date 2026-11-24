QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


VCPKG_ROOT = C:/Users/ilavo/source/repos/OOP/vcpkg
VCPKG_INSTALLED = $$VCPKG_ROOT/installed/x64-windows

INCLUDEPATH += $$VCPKG_INSTALLED/include

# Выбираем библиотеку и папку приложения для текущей конфигурации.
CONFIG(debug, debug|release) {
    MU_PREFIX = $$VCPKG_INSTALLED/debug
    DESTDIR = $$OUT_PWD/debug
} else {
    MU_PREFIX = $$VCPKG_INSTALLED
    DESTDIR = $$OUT_PWD/release
}

# muparser.lib используется при сборке.
LIBS += -L"$$MU_PREFIX/lib" -lmuparser

# muparser.dll нужна при запуске. Копируем её рядом с EXE.
MU_DLL = $$MU_PREFIX/bin/muparser.dll

muparser_runtime.target = $$DESTDIR/muparser.dll
muparser_runtime.depends = $$MU_DLL
muparser_runtime.commands = $(QINSTALL) $$shell_quote($$shell_path($$MU_DLL)) $$shell_quote($$shell_path($$muparser_runtime.target))

QMAKE_EXTRA_TARGETS += muparser_runtime
PRE_TARGETDEPS += $$muparser_runtime.target

DEFINES += _UNICODE
CONFIG += c++17

message("INCLUDEPATH: $$INCLUDEPATH")
message("LIBS: $$LIBS")

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    functionrepository.cpp \
    graphcanvas.cpp \
    graphfunction.cpp \
    graphrenderer.cpp \
    main.cpp \
    mainwindow.cpp \
    muparserevaluator.cpp \
    viewport.cpp

HEADERS += \
    functionrepository.h \
    graphcanvas.h \
    graphfunction.h \
    graphrenderer.h \
    mainwindow.h \
    muparserevaluator.h \
    viewport.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
