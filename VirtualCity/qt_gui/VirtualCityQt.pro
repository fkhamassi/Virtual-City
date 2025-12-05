QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Vous pouvez faire en sorte que votre code échoue à la compilation si vous utilisez des API obsolètes.
# Pour ce faire, décommentez la ligne suivante.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../src/Batiment.cpp \
    ../src/Maison.cpp \
    ../src/Parc.cpp \
    ../src/Service.cpp \
    ../src/Usine.cpp \
    ../src/Ville.cpp \
    ../src/Simulation.cpp

HEADERS += \
    mainwindow.h \
    ../src/Batiment.h \
    ../src/Maison.h \
    ../src/Parc.h \
    ../src/Service.h \
    ../src/Usine.h \
    ../src/Ville.h \
    ../src/Simulation.h

FORMS += \
    mainwindow.ui

# Répertoires d'inclusion
INCLUDEPATH += ../src

# Paramètres par défaut pour la cible.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
